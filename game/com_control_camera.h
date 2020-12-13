#pragma once

#include "../common/entity.h"
#include "../common/matrix.h"

typedef struct control_camera {
	vec4 start_color;
	vec4 end_color;
} ControlCamera;

struct world;
ControlCamera* mix_control_camera(struct world* world, Entity entity);
