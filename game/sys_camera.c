#include <stdint.h>
#include <stdlib.h>

#include "../common/matrix.h"

#include "client.h"
#include "com_camera.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_CAMERA;

static inline void update(struct client* client, struct world* world, entity entity)
{
	Transform* transform = world->transform[entity];
	Camera* camera = world->camera[entity];

	if (client->resized) {
		float aspect = (float)client->width / (float)client->height;
		if (aspect > 1.0) {
			// Landscape orientation.
			mat4_perspective(&camera->projection,
					camera->fov_y,
					aspect,
					camera->near,
					camera->far);
		} else {
			// Portrait orientation.
			mat4_perspective(&camera->projection,
					camera->fov_y / aspect,
					aspect,
					camera->near,
					camera->far);
		}
	}
	mat4_multiply(&camera->pv, &camera->projection, &transform->self);
}

void sys_camera(struct client* client, struct world* world)
{
	client->camera = NULL;

	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i);

			// Support only one camera per scene.
			client->camera = world->camera[i];
			return;
		}
	}
}
