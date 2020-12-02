#pragma once
#include <stdbool.h>
#include <stdint.h>

#include "../common/gl.h"
#include "../common/material.h"
#include "../common/mesh.h"
#include "index.h"

struct render_target {
	GLuint framebuffer;
	uint32_t width;
	uint32_t height;
};

struct input_state {
	int16_t arrow_up;
	int16_t arrow_down;
	int16_t arrow_left;
	int16_t arrow_right;
	int16_t key_w;
	int16_t key_s;
	int16_t key_a;
	int16_t key_d;
	int16_t mouse_x;
	int16_t mouse_y;
};

struct client {
	float delta;
	int32_t width;
	int32_t height;
	bool resized;

	struct input_state input_state;
	struct input_state input_delta;

	struct render_target targets[FRAMEBUFFERS_LENGTH];
	struct material materials[MATERIALS_LENGTH];
	struct mesh meshes[MESHES_LENGTH];
	GLuint textures[TEXTURES_LENGTH];

	union camera* cameras[3];
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
