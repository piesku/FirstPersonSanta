#include <stdbool.h>
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "client.h"
#include "com_light.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_LIGHT;

static inline void update(struct client* client, struct world* world, Entity entity, int32_t idx)
{
	Transform* transform = world->transform[entity];
	Light* light = world->light[entity];

	vec3 world_position;
	mat4_get_translation(&world_position, &transform->world);
	client->lights.positions[4 * idx + 0] = world_position.x;
	client->lights.positions[4 * idx + 1] = world_position.y;
	client->lights.positions[4 * idx + 2] = world_position.z;
	client->lights.positions[4 * idx + 3] = (float)light->kind;

	switch (light->kind) {
		case LIGHT_POINT:
			client->lights.colors[4 * idx + 0] = light->point.color.x;
			client->lights.colors[4 * idx + 1] = light->point.color.y;
			client->lights.colors[4 * idx + 2] = light->point.color.z;
			client->lights.colors[4 * idx + 3] = light->point.range;
			break;
		case LIGHT_SPOT:
			client->lights.colors[4 * idx + 0] = light->spot.color.x;
			client->lights.colors[4 * idx + 1] = light->spot.color.y;
			client->lights.colors[4 * idx + 2] = light->spot.color.z;
			client->lights.colors[4 * idx + 3] = light->spot.range;

			vec3 world_forward;
			mat4_get_forward(&world_forward, &transform->world);
			client->lights.directions[4 * idx + 0] = world_forward.x;
			client->lights.directions[4 * idx + 1] = world_forward.y;
			client->lights.directions[4 * idx + 2] = world_forward.z;
			client->lights.directions[4 * idx + 3] = light->spot.angle;
			break;
		case LIGHT_OFF:
			break;
	}
}

void sys_light(struct client* client, struct world* world)
{
	client->lights = (struct lights){
			.positions = {0},
			.colors = {0},
			.directions = {0},
	};
	int32_t counter = 0;
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i, counter);
			counter++;
		}
	}
}
