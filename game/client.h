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

struct client {
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

void client_setup(struct client* client, int32_t width, int32_t height);
void client_resize(struct client* client, int32_t width, int32_t height);
void client_teardown(struct client* client);

struct world;

void client_world_update(struct client* client, struct world* world, float delta);
void client_frame_update(struct client* client, struct world* world);
void client_input_reset(struct client* client);
