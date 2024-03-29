#include "com_camera.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

CameraDisplay* mix_camera_display(struct world* world, Entity entity)
{
	Camera* camera = xmalloc(sizeof(*camera));
	*camera = (Camera){
			.display = {
					.kind = CAMERA_DISPLAY,
					.clear_color = (vec4){0.9f, 0.9f, 0.9f, 1.0f},
			},
	};

	mat4_identity(&camera->display.projection);
	mat4_identity(&camera->display.eye.pv);

	world->signature[entity] |= HAS_CAMERA;
	world->camera[entity] = camera;
	return &camera->display;
}

CameraFramebuffer* mix_camera_framebuffer(struct world* world, Entity entity)
{
	Camera* camera = xmalloc(sizeof(*camera));
	*camera = (Camera){
			.framebuffer = {
					.kind = CAMERA_FRAMEBUFFER,
					.clear_color = (vec4){0.9f, 0.9f, 0.9f, 1.0f},
			},
	};

	mat4_identity(&camera->framebuffer.projection);
	mat4_identity(&camera->framebuffer.eye.pv);

	world->signature[entity] |= HAS_CAMERA;
	world->camera[entity] = camera;
	return &camera->framebuffer;
}
