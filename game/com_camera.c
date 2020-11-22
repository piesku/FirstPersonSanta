#include "com_camera.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

Camera* mix_camera(struct world* world, entity entity)
{
	Camera* camera = xmalloc(sizeof(*camera));
	*camera = (Camera){
			.fov_y = 1.0,
			.near = 0.1,
			.far = 100.0,
			.projection = {0},
			.pv = {0},
	};

	mat4_identity(camera->projection);
	mat4_identity(camera->pv);

	world->signature[entity] |= HAS_CAMERA;
	return world->camera[entity] = camera;
}
