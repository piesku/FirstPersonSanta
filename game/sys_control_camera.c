#include <stdbool.h>
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"

#include "client.h"
#include "com_camera.h"
#include "com_control_camera.h"
#include "com_transform.h"
#include "world.h"

static int QUERY = HAS_CAMERA | HAS_CONTROL_CAMERA;

static inline void update(struct world* world, Entity entity, float t)
{
	Camera* camera = world->camera[entity];
	ControlCamera* control = world->control_camera[entity];

	switch (camera->kind) {
		case CAMERA_DISPLAY:
			vec4_lerp(&camera->display.clear_color, &control->start_color, &control->end_color, t);
			break;
		case CAMERA_FRAMEBUFFER:
			vec4_lerp(&camera->framebuffer.clear_color, &control->start_color, &control->end_color, t);
			break;
	}
}

void sys_control_camera(struct client* client, struct world* world, float delta)
{
	client->time_left -= delta;

	if (client->time_left < 0) {
		// Game Over.
		(void)client;
	}

	float t = 1 - client->time_left / client->time_total;

	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i, t);
		}
	}
}
