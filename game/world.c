#include "world.h"

#include <stdlib.h>

#include "com_transform.h"

struct world* create_world(void)
{
	struct world* world = calloc(1, sizeof(*world));
	return world;
}

void destroy_world(struct world* world)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if (world->signature[i] & HAS_TRANSFORM) {
			Transform* transform = world->transform[i];
			entity_list_destroy(&transform->children);
		}
	}

	free(world);
}

Entity create_entity(struct world* world)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if (world->signature[i] == 0) {
			return i;
		}
	}

	return 0;
}

void destroy_entity(struct world* world, Entity entity)
{
	if (entity < MAX_ENTITIES) {
		world->signature[entity] = 0;
	}
}
