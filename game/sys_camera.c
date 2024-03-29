#include <stdint.h>
#include <stdlib.h>

#include "../common/entity.h"
#include "../common/matrix.h"

#include "client.h"
#include "com_camera.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_CAMERA;

static inline void update_display(struct client* client, struct world* world, Entity entity)
{
	Transform* transform = world->transform[entity];
	CameraDisplay* camera = &world->camera[entity]->display;

	if (client->resized) {
		float aspect = (float)client->width / (float)client->height;
		if (aspect > 1.0) {
			// Landscape orientation.
			mat4_perspective(&camera->projection,
					camera->fov_y,
					aspect,
					camera->near,
					camera->far);
			mat4_invert(&camera->eye.unprojection, &camera->projection);
		} else {
			// Portrait orientation.
			mat4_perspective(&camera->projection,
					camera->fov_y / aspect,
					aspect,
					camera->near,
					camera->far);
			mat4_invert(&camera->eye.unprojection, &camera->projection);
		}
	}

	mat4_copy(&camera->eye.world, &transform->world);
	mat4_copy(&camera->eye.view, &transform->self);
	mat4_multiply(&camera->eye.pv, &camera->projection, &camera->eye.view);
}

static inline void update_framebuffer(struct client* client, struct world* world, Entity entity)
{
	Transform* transform = world->transform[entity];
	CameraFramebuffer* camera = &world->camera[entity]->framebuffer;

	if (client->resized) {
		struct render_target* target = &client->targets[camera->target];
		float aspect = (float)target->width / (float)target->height;
		if (aspect > 1.0) {
			// Landscape orientation.
			mat4_perspective(&camera->projection,
					camera->fov_y,
					aspect,
					camera->near,
					camera->far);
			mat4_invert(&camera->eye.unprojection, &camera->projection);
		} else {
			// Portrait orientation.
			mat4_perspective(&camera->projection,
					camera->fov_y / aspect,
					aspect,
					camera->near,
					camera->far);
			mat4_invert(&camera->eye.unprojection, &camera->projection);
		}
	}

	mat4_copy(&camera->eye.world, &transform->world);
	mat4_copy(&camera->eye.view, &transform->self);
	mat4_multiply(&camera->eye.pv, &camera->projection, &camera->eye.view);
}

void sys_camera(struct client* client, struct world* world)
{
	client->camera_default = NULL;
	client->camera_minimap = NULL;

	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Camera* camera = world->camera[i];
			switch (camera->kind) {
				case CAMERA_DISPLAY:
					client->camera_default = camera;
					update_display(client, world, i);
					break;
				case CAMERA_FRAMEBUFFER:
					if (client->camera_default == NULL) {
						client->camera_default = camera;
					} else {
						client->camera_minimap = &camera->framebuffer;
					}
					update_framebuffer(client, world, i);
					break;
			}
		}
	}
}
