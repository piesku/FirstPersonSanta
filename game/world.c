#include "world.h"

#include <stdlib.h>

struct world* create_world(void)
{
	struct world* world = calloc(1, sizeof(*world));
	return world;
}

void destroy_world(struct world* world)
{
	free(world);
}

entity create_entity(struct world* world)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if (world->signature[i] == 0) {
			return i;
		}
	}

	return 0;
}

void destroy_entity(struct world* world, entity entity)
{
	if (entity < MAX_ENTITIES) {
		world->signature[entity] = 0;
	}
}
