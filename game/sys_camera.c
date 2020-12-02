#include <stdint.h>
#include <stdlib.h>

#include "../common/matrix.h"

#include "client.h"
#include "com_camera.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_CAMERA;

static inline void update_display(struct client* client, struct world* world, entity entity)
{
	Transform* transform = world->transform[entity];
	CameraDisplay* camera = &world->camera[entity]->display;

	if (client->resized) {
		float aspect = (float)client->width / (float)client->height;
		if (aspect > 1.0) {
			// Landscape orientation.
			mat4_perspective(camera->projection,
					camera->fov_y,
					aspect,
					camera->near,
					camera->far);
		} else {
			// Portrait orientation.
			mat4_perspective(camera->projection,
					camera->fov_y / aspect,
					aspect,
					camera->near,
					camera->far);
		}
	}
	mat4_multiply(camera->eye.pv, camera->projection, transform->self);
}

static inline void update_framebuffer(struct client* client, struct world* world, entity entity)
{
	Transform* transform = world->transform[entity];
	CameraFramebuffer* camera = &world->camera[entity]->framebuffer;
	mat4_multiply(camera->eye.pv, camera->projection, transform->self);
}

void sys_camera(struct client* client, struct world* world)
{
	client->cameras[0] = NULL;
	client->cameras[1] = NULL;
	client->cameras[2] = NULL;

	int counter = 1;

	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Camera* camera = world->camera[i];
			switch (camera->kind) {
				case CAMERA_DISPLAY:
					client->cameras[0] = camera;
					update_display(client, world, i);
					break;
				case CAMERA_FRAMEBUFFER:
					client->cameras[counter++] = camera;
					update_framebuffer(client, world, i);
					break;
			}
		}
	}
}
