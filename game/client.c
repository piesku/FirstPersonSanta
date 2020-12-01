#include "client.h"

#include <stdlib.h>
#include <string.h>

#include "../common/matrix.h"
#include "../common/texture.h"

struct material mat_colored_unlit(void);
struct material mat_textured_unlit(void);
struct mesh mesh_cube(void);

void sys_camera(struct client* client, struct world* world);
void sys_collide(struct client* client, struct world* world, float delta);
void sys_control_keyboard(struct client* client, struct world* world, float delta);
void sys_control_mouse(struct client* client, struct world* world, float delta);
void sys_light(struct client* client, struct world* world);
void sys_move(struct client* client, struct world* world, float delta);
void sys_physics_integrate(struct client* client, struct world* world, float delta);
void sys_physics_kinematic(struct client* client, struct world* world, float delta);
void sys_physics_resolve(struct client* client, struct world* world, float delta);
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

	client->materials[MAT_COLORED_UNLIT] = mat_colored_unlit();
	client->materials[MAT_TEXTURED_UNLIT] = mat_textured_unlit();
	client->meshes[MESH_CUBE] = mesh_cube();

	client->textures[TEX_RENDER_RGBA] = create_texture_rgba(256, 256);
	client->textures[TEX_RENDER_DEPTH] = create_texture_depth(256, 256);

	client->cameras[0] = NULL;
	client->cameras[1] = NULL;

	// OpenGL 3.3. (core profile, i.e. in strict mode) requires at least one VAO.
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void client_resize(struct client* client, int32_t width, int32_t height)
{
	client->width = width;
	client->height = height;
	client->resized = true;
}

void client_teardown(struct client* client)
{
	// Delete shaders.
	for (int8_t i = 0; i < MATERIALS_LENGTH; i++) {
		glDeleteProgram(client->materials[i].program);
	}
	// Delete buffer objects.
	for (int8_t i = 0; i < MESHES_LENGTH; i++) {
		glDeleteBuffers(1, &client->meshes[i].vertex_buffer);
		glDeleteBuffers(1, &client->meshes[i].index_buffer);
	}
	// Delete textures.
	glDeleteTextures(TEXTURES_LENGTH, client->textures);
}

void client_world_update(struct client* client, struct world* world, float delta)
{
	// Input.
	sys_control_keyboard(client, world, delta);
	sys_control_mouse(client, world, delta);

	// Game logic.
	sys_move(client, world, delta);
	sys_transform(client, world, delta);

	// Collisions and physics.
	sys_physics_integrate(client, world, delta);
	sys_transform(client, world, delta);
	sys_physics_kinematic(client, world, delta);
	sys_collide(client, world, delta);
	sys_physics_resolve(client, world, delta);
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
