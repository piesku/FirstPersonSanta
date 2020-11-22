#include <stdint.h>
#include <stdlib.h>

#include "../common/matrix.h"

#include "canvas.h"
#include "com_camera.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_CAMERA;

static inline void update(struct canvas* canvas, struct world* world, entity entity)
{
	Transform* transform = world->transform[entity];
	Camera* camera = world->camera[entity];

	if (canvas->resized) {
		float aspect = (float)canvas->width / (float)canvas->height;
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
	mat4_multiply(camera->pv, camera->projection, transform->self);
}

void sys_camera(struct canvas* canvas, struct world* world)
{
	canvas->camera = NULL;

	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(canvas, world, i);

			// Support only one camera per scene.
			canvas->camera = world->camera[i];
			return;
		}
	}
}
