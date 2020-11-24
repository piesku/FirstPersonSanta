#include "client.h"

#include <stdlib.h>
#include <string.h>

#include "../common/matrix.h"

struct material mat_basic_colored(void);
struct material mat_basic_textured(void);
struct material mat_diffuse_gouraud(void);

struct mesh mesh_cube(void);

void sys_camera(struct client* client, struct world* world);
void sys_control_keyboard(struct client* client, struct world* world, float delta);
void sys_light(struct client* client, struct world* world);
void sys_move(struct client* client, struct world* world, float delta);
void sys_render(struct client* client, struct world* world);
void sys_transform(struct client* client, struct world* world, float delta);


void client_setup(struct client* client, int32_t width, int32_t height)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glViewport(0, 0, width, height);

	client->width = width;
	client->height = height;
	client->resized = true;

	client->materials[MAT_BASIC_COLORED] = mat_basic_colored();
	client->meshes[MESH_CUBE] = mesh_cube();

	client->camera = NULL;
}

void client_resize(struct client* client, int32_t width, int32_t height)
{
	client->width = width;
	client->height = height;
	client->resized = true;
}

void client_teardown(struct client* client)
{
	for (int8_t i = 0; i < MATERIALS_LENGTH; i++) {
		glDeleteProgram(client->materials[i].program);
	}
	for (int8_t i = 0; i < MESHES_LENGTH; i++) {
		glDeleteBuffers(1, &client->meshes[i].vertex_buffer);
		glDeleteBuffers(1, &client->meshes[i].index_buffer);
	}
}

void client_world_update(struct client* client, struct world* world, float delta)
{
	sys_control_keyboard(client, world, delta);
	sys_move(client, world, delta);
	sys_transform(client, world, delta);
}

void client_frame_update(struct client* client, struct world* world)
{
	sys_camera(client, world);
	sys_light(client, world);
	sys_render(client, world);

	client->resized = false;
}

void client_input_reset(struct client* client)
{
	client->input_delta = (const struct input_state){0};
}
