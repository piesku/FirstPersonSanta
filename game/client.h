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
	int16_t key_space;
	int32_t mouse_x;
	int32_t mouse_y;
	int16_t mouse_button_left;
};

struct client {
	float delta;
	int32_t width;
	int32_t height;
	bool resized;

	struct world* world;
	void (*next_scene)(struct world*);

	struct input_state input_state;
	struct input_state input_delta;

	struct render_target targets[RENDER_TARGETS_LENGTH];
	struct material materials[MATERIALS_LENGTH];
	struct mesh meshes[MESHES_LENGTH];
	GLuint textures[TEXTURES_LENGTH];

	union camera* camera_default;
	struct camera_framebuffer* camera_minimap;
	struct lights {
		float positions[4 * 8];
		float colors[4 * 8];
		float directions[4 * 8];
	} lights;

	// TODO Game state should be external to client.
	float time_total;
	float time_left;
};

void client_setup(struct client* client, int32_t width, int32_t height);
void client_resize(struct client* client, int32_t width, int32_t height);
void client_teardown(struct client* client);

void client_world_update(struct client* client, float delta);
void client_frame_update(struct client* client);
void client_input_reset(struct client* client);
