#include <stdint.h>

#include "../common/matrix.h"
#include "client.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM;

static inline void set_children_as_dirty(struct world* world, Transform* parent)
{
	for (int i = 0; i < MAX_CHILDREN; i++) {
		entity child = parent->children[i];
		if (child) {
			Transform* transform = world->transform[child];
			transform->dirty = true;
			set_children_as_dirty(world, transform);
		}
	}
}

static inline void update(struct world* world, entity entity)
{
	Transform* transform = world->transform[entity];
	if (transform->dirty) {
		set_children_as_dirty(world, transform);
		transform->dirty = false;

		mat4_compose(transform->world,
				transform->translation,
				transform->rotation,
				transform->scale);
		if (transform->parent) {
			mat4_multiply(transform->world,
					world->transform[transform->parent]->world,
					transform->world);
		}
		mat4_invert(transform->self, transform->world);
	}
}

void sys_transform(struct client* client, struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i);
		}
	}
}