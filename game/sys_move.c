#include <stdbool.h>
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_MOVE;
static const quat NO_ROTATION = {0.0f, 0.0f, 0.0f, 1.0f};

static inline void update(struct world* world, entity entity, float delta)
{
	Move* move = world->move[entity];
	Transform* transform = world->transform[entity];

	if (move->dirty & MOVE_DIRTY_DIRECTION) {
		vec3 direction;

		// Directions are not normalized to allow them to express slower
		// movement from a gamepad input. They can also cancel each other out.
		// They may not, however, intensify one another; hence max amount is 1.
		float amount = vec3_length(&move->direction);
		if (amount > 1.0f)
			amount = 1.0f;

		// Transform the direction into the world or the parent space. This will
		// also scale the result by the scale encoded in the transform.
		vec3_transform_direction(&direction, &move->direction, &transform->world);
		if (transform->parent) {
			vec3_transform_direction(&direction,
					&direction,
					&world->transform[transform->parent]->self);
		}

		// Normalize the direction to remove the transform's scale. The length
		// of the orignal direction is now lost.
		vec3_normalize(&direction, &direction);

		// Scale by the amount and distance traveled in this tick.
		vec3_scale(&direction, &direction, amount * move->movement_speed * delta);

		// Apply the movement to the transform.
		vec3_add(&transform->translation, &transform->translation, &direction);
		transform->dirty = true;

		move->dirty &= ~MOVE_DIRTY_DIRECTION;
	}

	if (move->dirty & MOVE_DIRTY_LOCAL_ROTATION) {
		quat rotation;
		float t = move->rotation_speed / PI * delta;
		if (t > 1.0f)
			t = 1.0f;
		quat_slerp(&rotation, &NO_ROTATION, &move->local_rotation, t);

		// Pre-multiply.
		quat_multiply(&transform->rotation, &rotation, &transform->rotation);
		transform->dirty = true;

		move->dirty &= ~MOVE_DIRTY_LOCAL_ROTATION;
	}

	if (move->dirty & MOVE_DIRTY_SELF_ROTATION) {
		quat rotation;
		float t = move->rotation_speed / PI * delta;
		if (t > 1.0f)
			t = 1.0f;
		quat_slerp(&rotation, &NO_ROTATION, &move->self_rotation, t);

		// Post-multiply.
		quat_multiply(&transform->rotation, &transform->rotation, &rotation);
		transform->dirty = true;

		move->dirty &= ~MOVE_DIRTY_SELF_ROTATION;
	}
}

void sys_move(struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i, delta);
		}
	}
}
