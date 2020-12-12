#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM;

static inline void update_transform(struct world* world, Transform* transform)
{
	transform->dirty = false;

	mat4_compose(&transform->world,
			&transform->translation,
			&transform->rotation,
			&transform->scale);

	if (transform->parent) {
		mat4_multiply(&transform->world,
				&world->transform[transform->parent]->world,
				&transform->world);
	}

	mat4_invert(&transform->self, &transform->world);

	for (size_t i = 0; i < transform->children.size; i++) {
		Entity child = transform->children.entities[i];
		if (child) {
			update_transform(world, world->transform[child]);
		}
	}
}

void sys_transform(struct world* world)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Transform* transform = world->transform[i];
			if (transform->dirty) {
				update_transform(world, transform);
			}
		}
	}
}
