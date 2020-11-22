#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"
#include "client.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_MOVE;

static inline void update(struct client* client, struct world* world, entity entity, float delta)
{
	Transform* transform = world->transform[entity];
	Move* move = world->move[entity];

	if (move->dirty & MOVE_DIRTY_DIRECTION) {
		vec3 direction;
		float amount = vec3_length(move->direction);
		if (amount > 1.0)
			amount = 1.0;
		vec3_transform_direction(direction, move->direction, transform->world);
		vec3_normalize(direction, direction);
		vec3_scale(direction, direction, amount * move->movement_speed * delta);
		vec3_add(transform->translation, transform->translation, direction);
		transform->dirty = true;
		move->dirty = MOVE_DIRTY_NONE;
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