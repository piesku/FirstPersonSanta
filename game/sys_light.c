#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"
#include "canvas.h"
#include "com_light.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_LIGHT;

static inline void update(struct canvas* canvas, struct world* world, entity entity, int32_t idx)
{
	Transform* transform = world->transform[entity];
	Light* light = world->light[entity];

	vec3 world_position;
	mat4_get_translation(world_position, transform->world);

	if (light->kind == LIGHT_DIRECTIONAL) {
		// For directional lights, their normalized position in the world
		// describes the light's normal.
		vec3_normalize(world_position, world_position);
	}

	canvas->lights.positions[4 * idx + 0] = world_position[0];
	canvas->lights.positions[4 * idx + 1] = world_position[1];
	canvas->lights.positions[4 * idx + 2] = world_position[2];
	canvas->lights.positions[4 * idx + 3] = (float)light->kind;

	canvas->lights.details[4 * idx + 0] = light->color[0];
	canvas->lights.details[4 * idx + 1] = light->color[1];
	canvas->lights.details[4 * idx + 2] = light->color[2];
	canvas->lights.details[4 * idx + 3] = light->intensity;
}

void sys_light(struct canvas* canvas, struct world* world)
{
	canvas->lights = (const struct lights){
			.positions = {0},
			.details = {0},
	};

	int32_t counter = 0;
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(canvas, world, i, counter);
			counter++;
		}
	}
}
