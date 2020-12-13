#include "com_control_camera.h"

#include "../common/malloc.h"
#include "world.h"

ControlCamera* mix_control_camera(struct world* world, Entity entity)
{
	ControlCamera* control = xmalloc(sizeof(*control));
	*control = (ControlCamera){0};

	world->signature[entity] |= HAS_CONTROL_CAMERA;
	return world->control_camera[entity] = control;
}
