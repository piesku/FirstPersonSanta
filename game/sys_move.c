#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"
#include "client.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_MOVE;
static const quat NO_ROTATION = {0.0f, 0.0f, 0.0f, 1.0f};

static inline void update(struct client* client, struct world* world, entity entity, float delta)
{
	Move* move = world->move[entity];
	Transform* transform = world->transform[entity];

	if (move->dirty & MOVE_DIRTY_DIRECTION) {
		vec3 direction;
		float amount = vec3_length(move->direction);
		if (amount > 1.0f)
			amount = 1.0f;
		vec3_transform_direction(direction, move->direction, transform->world);
		vec3_normalize(direction, direction);
		vec3_scale(direction, direction, amount * move->movement_speed * delta);

		vec3_add(transform->translation, transform->translation, direction);
		transform->dirty = true;

		move->dirty &= ~MOVE_DIRTY_DIRECTION;
		move->direction[0] = 0;
		move->direction[1] = 0;
		move->direction[2] = 0;
	}

	if (move->dirty & MOVE_DIRTY_LOCAL_ROTATION) {
		quat rotation;
		float t = move->rotation_speed / PI * delta;
		if (t > 1.0f)
			t = 1.0f;
		quat_slerp(rotation, NO_ROTATION, move->local_rotation, t);

		// Pre-multiply.
		quat_multiply(transform->rotation, rotation, transform->rotation);
		transform->dirty = true;

		move->dirty &= ~MOVE_DIRTY_LOCAL_ROTATION;
	}
}

void sys_move(struct client* client, struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i, delta);
		}
	}
}