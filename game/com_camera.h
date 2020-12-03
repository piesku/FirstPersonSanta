#pragma once
#include "../common/entity.h"
#include "../common/matrix.h"

typedef struct camera {
	float fov_y;
	float near;
	float far;
	mat4 projection;
	mat4 pv;
} Camera;

struct world;
Camera* mix_camera(struct world* world, entity entity);
