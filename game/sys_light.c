#include <stdbool.h>
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "client.h"
#include "com_light.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_LIGHT;

static inline void update(struct client* client, struct world* world, entity entity, int32_t idx)
{
	Transform* transform = world->transform[entity];
	Light* light = world->light[entity];

	vec3 world_position;
	mat4_get_translation(&world_position, &transform->world);

	if (light->kind == LIGHT_DIRECTIONAL) {
		vec3_normalize(&world_position, &world_position);
	}

	switch (light->kind) {
		case LIGHT_DIRECTIONAL:
			// The normalized world position describes the light's normal.
			vec3_normalize(&world_position, &world_position);

			client->lights.details[4 * idx + 0] = light->directional.color.x;
			client->lights.details[4 * idx + 1] = light->directional.color.y;
			client->lights.details[4 * idx + 2] = light->directional.color.z;
			client->lights.details[4 * idx + 3] = light->directional.range;
			break;
		case LIGHT_POINT:
			client->lights.details[4 * idx + 0] = light->point.color.x;
			client->lights.details[4 * idx + 1] = light->point.color.y;
			client->lights.details[4 * idx + 2] = light->point.color.z;
			client->lights.details[4 * idx + 3] = light->point.range;
			break;
		case LIGHT_OFF:
			break;
	}

	client->lights.positions[4 * idx + 0] = world_position.x;
	client->lights.positions[4 * idx + 1] = world_position.y;
	client->lights.positions[4 * idx + 2] = world_position.z;
	client->lights.positions[4 * idx + 3] = (float)light->kind;
}

void sys_light(struct client* client, struct world* world)
{
	client->lights = (const struct lights){
			.positions = {0},
			.details = {0},
	};

	int32_t counter = 0;
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i, counter);
			counter++;
		}
	}
}
