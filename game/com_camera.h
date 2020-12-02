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
	mat4 view;
	mat4 pv;
};

typedef struct camera_display {
	enum camera_kind kind;
	vec4 clear_color;
	float fov_y;
	float near;
	float far;
	mat4 projection;
	struct eye eye;
} CameraDisplay;

typedef struct camera_framebuffer {
	enum camera_kind kind;
	vec4 clear_color;
	float fov_y;
	float near;
	float far;
	mat4 projection;
	struct eye eye;
	enum framebuffer_index target;
	enum texture_index render_texture;
	enum texture_index depth_texture;
	uint32_t width;
	uint32_t height;
} CameraFramebuffer;

typedef union camera {
	enum camera_kind kind;
	CameraDisplay display;
	CameraFramebuffer framebuffer;
} Camera;

struct world;
CameraDisplay* mix_camera_display(struct world* world, entity entity);
CameraFramebuffer* mix_camera_framebuffer(struct world* world, entity entity);
