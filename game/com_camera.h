#pragma once

#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"

#include "index.h"

enum camera_kind {
	CAMERA_DISPLAY,
	CAMERA_FRAMEBUFFER,
};

struct eye {
	mat4 world;
	mat4 view;
	mat4 pv;
	mat4 unprojection;
};

typedef struct camera_display {
	enum camera_kind kind;
	struct eye eye;
	vec4 clear_color;
	float fov_y;
	float near;
	float far;
	mat4 projection;
} CameraDisplay;

typedef struct camera_framebuffer {
	enum camera_kind kind;
	struct eye eye;
	vec4 clear_color;
	float fov_y;
	float near;
	float far;
	mat4 projection;
	enum render_target_index target;
} CameraFramebuffer;

typedef union camera {
	enum camera_kind kind;
	CameraDisplay display;
	CameraFramebuffer framebuffer;
} Camera;

struct world;
CameraDisplay* mix_camera_display(struct world* world, Entity entity);
CameraFramebuffer* mix_camera_framebuffer(struct world* world, Entity entity);
