#include "client.h"

#include <stdlib.h>
#include <string.h>

#include "../common/matrix.h"
#include "../common/texture.h"

struct material mat_colored_unlit(void);
struct material mat_textured_unlit(void);
struct material mat_postprocess(void);
struct mesh mesh_cube(void);
struct mesh mesh_quad(void);

void sys_camera(struct client* client, struct world* world);
void sys_collide(struct client* client, struct world* world, float delta);
void sys_control_keyboard(struct client* client, struct world* world, float delta);
void sys_control_mouse(struct client* client, struct world* world, float delta);
void sys_light(struct client* client, struct world* world);
void sys_move(struct client* client, struct world* world, float delta);
void sys_physics_integrate(struct client* client, struct world* world, float delta);
void sys_physics_kinematic(struct client* client, struct world* world, float delta);
void sys_physics_resolve(struct client* client, struct world* world, float delta);
void sys_postprocess(struct client* client, struct world* world);
void sys_render(struct client* client, struct world* world);
void sys_transform(struct client* client, struct world* world, float delta);

void client_setup(struct client* client, int32_t width, int32_t height)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	client_resize(client, width, height);

	{
		struct render_target* target = &client->targets[FB_RENDER];
		target->width = width;
		target->height = height;

		client->textures[TEX_RENDER_RGBA] = create_texture_rgba(target->width, target->height);
		client->textures[TEX_RENDER_DEPTH] = create_texture_depth(target->width, target->height);

		GLuint* fb = &target->framebuffer;
		glCreateFramebuffers(1, fb);
		glBindFramebuffer(GL_FRAMEBUFFER, *fb);

		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				client->textures[TEX_RENDER_RGBA],
				0);

		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D,
				client->textures[TEX_RENDER_DEPTH],
				0);
	}

	{
		struct render_target* target = &client->targets[FB_MINIMAP];
		target->width = 256;
		target->height = 256;

		client->textures[TEX_MINIMAP_RGBA] = create_texture_rgba(target->width, target->height);
		client->textures[TEX_MINIMAP_DEPTH] = create_texture_depth(target->width, target->height);

		GLuint* fb = &target->framebuffer;
		glCreateFramebuffers(1, fb);
		glBindFramebuffer(GL_FRAMEBUFFER, *fb);

		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				client->textures[TEX_MINIMAP_RGBA],
				0);

		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D,
				client->textures[TEX_MINIMAP_DEPTH],
				0);
	}

	client->materials[MAT_COLORED_UNLIT] = mat_colored_unlit();
	client->materials[MAT_TEXTURED_UNLIT] = mat_textured_unlit();
	client->materials[MAT_POSTPROCESS] = mat_postprocess();
	client->meshes[MESH_CUBE] = mesh_cube();
	client->meshes[MESH_QUAD] = mesh_quad();

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

	// Delete framebuffers.
	for (int8_t i = 0; i < FRAMEBUFFERS_LENGTH; i++) {
		glDeleteFramebuffers(1, &client->targets[i].framebuffer);
	}
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
	sys_postprocess(client, world);

	client->resized = false;
}

void client_input_reset(struct client* client)
{
	client->input_delta = (const struct input_state){0};
}
