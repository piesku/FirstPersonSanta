#pragma once
#include <stdbool.h>
#include <stdint.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include "../common/material.h"
#include "../common/mesh.h"
#include "../common/texture.h"
#include "index.h"

struct input_state {
	int16_t arrow_left;
	int16_t arrow_right;
};

struct canvas {
	float delta;
	int32_t width;
	int32_t height;
	bool resized;

	struct input_state input_state;
	struct input_state input_delta;

	GLuint assets[ASSETS_LENGTH];
	struct material materials[MATERIALS_LENGTH];
	struct mesh meshes[MESHES_LENGTH];

	struct camera* camera;
	struct lights {
		float positions[4 * 8];
		float details[4 * 8];
	} lights;
};

void canvas_setup(struct canvas* canvas, int32_t width, int32_t height);
void canvas_resize(struct canvas* canvas, int32_t width, int32_t height);
void canvas_teardown(struct canvas* canvas);

struct world;

void canvas_world_update(struct canvas* canvas, struct world* world, float delta);
void canvas_frame_update(struct canvas* canvas, struct world* world);
void canvas_input_reset(struct canvas* canvas);
