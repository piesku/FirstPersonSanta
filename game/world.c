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
		destroy_entity(world, i);
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

static inline void destroy_component_data(void* component_data)
{
	if (component_data != NULL) {
		free(component_data);
	}
}

void destroy_entity(struct world* world, Entity entity)
{
	if (entity < MAX_ENTITIES) {
		world->signature[entity] = 0;

		destroy_component_data(world->camera[entity]);
		destroy_component_data(world->collide[entity]);
		destroy_component_data(world->control_player[entity]);
		destroy_component_data(world->mimic[entity]);
		destroy_component_data(world->move[entity]);
		destroy_component_data(world->light[entity]);
		destroy_component_data(world->render[entity]);
		destroy_component_data(world->rigid_body[entity]);
		destroy_component_data(world->shoot[entity]);
		destroy_component_data(world->trigger[entity]);

		Transform* transform = world->transform[entity];
		if (transform != NULL) {
			entity_list_destroy(&transform->children);
			destroy_component_data(transform);
		}
	}
}
