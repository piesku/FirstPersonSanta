#include "world.h"

#include <stdlib.h>

#include "com_transform.h"

static inline void destroy_component_data(void** component_data)
{
	if (*component_data != NULL) {
		free(*component_data);
		*component_data = NULL;
	}
}

struct world* create_world(void)
{
	struct world* world = calloc(1, sizeof(*world));
	return world;
}

void destroy_world(struct world* world)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		world->signature[i] = 0;

		destroy_component_data((void**)&world->camera[i]);
		destroy_component_data((void**)&world->collide[i]);
		destroy_component_data((void**)&world->control_camera[i]);
		destroy_component_data((void**)&world->control_player[i]);
		destroy_component_data((void**)&world->mimic[i]);
		destroy_component_data((void**)&world->move[i]);
		destroy_component_data((void**)&world->light[i]);
		destroy_component_data((void**)&world->render[i]);
		destroy_component_data((void**)&world->rigid_body[i]);
		destroy_component_data((void**)&world->shoot[i]);
		destroy_component_data((void**)&world->trigger[i]);

		Transform* transform = world->transform[i];
		if (transform != NULL) {
			entity_list_destroy(&transform->children);
			destroy_component_data((void**)&world->transform[i]);
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
