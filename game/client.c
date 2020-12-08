#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/matrix.h"
#include "../common/texture.h"
#include "world.h"

struct material mat_colored_unlit(void);
struct material mat_textured_unlit(void);
struct material mat_postprocess(void);
struct mesh mesh_cube(void);
struct mesh mesh_quad(void);
struct mesh mesh_gift(void);
struct mesh mesh_monkey(void);
// Furniture.
struct mesh mesh_chair(void);
struct mesh mesh_lamp(void);
struct mesh mesh_sofa(void);

void sys_camera(struct client* client, struct world* world);
void sys_collide(struct world* world);
void sys_control_keyboard(struct client* client, struct world* world);
void sys_control_mouse(struct client* client, struct world* world);
void sys_light(struct client* client, struct world* world);
void sys_mimic(struct world* world);
void sys_move(struct world* world, float delta);
void sys_physics_integrate(struct world* world, float delta);
void sys_physics_kinematic(struct world* world, float delta);
void sys_physics_resolve(struct world* world);
void sys_postprocess(struct client* client);
void sys_render(struct client* client, struct world* world);
void sys_shoot(struct world* world, float delta);
void sys_transform(struct world* world);
void sys_trigger(struct client* client, struct world* world);

void client_setup(struct client* client, int32_t width, int32_t height)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	client_resize(client, width, height);

	{
		struct render_target* target = &client->targets[RENDER_TARGET_DEFAULT];
		target->width = width;
		target->height = height;

		client->textures[TEX_RENDER_RGBA] = create_texture_rgba(target->width, target->height);
		client->textures[TEX_RENDER_NORMALS] = create_texture_rgba(target->width, target->height);
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
				GL_COLOR_ATTACHMENT1,
				GL_TEXTURE_2D,
				client->textures[TEX_RENDER_NORMALS],
				0);

		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D,
				client->textures[TEX_RENDER_DEPTH],
				0);

		GLenum draw_buffers[2] = {
				GL_COLOR_ATTACHMENT0,
				GL_COLOR_ATTACHMENT1};
		glDrawBuffers(2, draw_buffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			printf("Failed to set up the framebuffer.\n");
			exit(1);
		}
	}

	{
		struct render_target* target = &client->targets[RENDER_TARGET_MINIMAP];
		target->width = 256;
		target->height = 256;

		client->textures[TEX_MINIMAP_RGBA] = create_texture_rgba(target->width, target->height);
		client->textures[TEX_MINIMAP_NORMALS] = create_texture_rgba(target->width, target->height);
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
				GL_COLOR_ATTACHMENT1,
				GL_TEXTURE_2D,
				client->textures[TEX_MINIMAP_NORMALS],
				0);

		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D,
				client->textures[TEX_MINIMAP_DEPTH],
				0);

		GLenum draw_buffers[2] = {
				GL_COLOR_ATTACHMENT0,
				GL_COLOR_ATTACHMENT1};
		glDrawBuffers(2, draw_buffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			printf("Failed to set up the framebuffer.\n");
			exit(1);
		}
	}

	client->materials[MAT_COLORED_UNLIT] = mat_colored_unlit();
	client->materials[MAT_TEXTURED_UNLIT] = mat_textured_unlit();
	client->materials[MAT_POSTPROCESS] = mat_postprocess();
	client->meshes[MESH_CUBE] = mesh_cube();
	client->meshes[MESH_QUAD] = mesh_quad();
	client->meshes[MESH_GIFT] = mesh_gift();
	client->meshes[MESH_MONKEY] = mesh_monkey();
	client->meshes[MESH_CHAIR] = mesh_chair();
	client->meshes[MESH_LAMP] = mesh_lamp();
	client->meshes[MESH_SOFA] = mesh_sofa();

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
	for (int8_t i = 0; i < RENDER_TARGETS_LENGTH; i++) {
		glDeleteFramebuffers(1, &client->targets[i].framebuffer);
	}
}

void client_world_update(struct client* client, float delta)
{
	struct world* world = client->world;

	// Input.
	sys_control_keyboard(client, world);
	sys_control_mouse(client, world);

	// Game logic.
	sys_shoot(world, delta);
	sys_move(world, delta);
	sys_mimic(world);
	sys_transform(world);

	// Collisions and physics.
	sys_physics_integrate(world, delta);
	sys_transform(world);
	sys_physics_kinematic(world, delta);
	sys_collide(world);
	sys_trigger(client, world);
	sys_physics_resolve(world);
	sys_transform(world);
}

void client_frame_update(struct client* client)
{
	struct world* world = client->world;

	sys_camera(client, world);
	sys_light(client, world);
	sys_render(client, world);
	sys_postprocess(client);

	if (client->next_scene != NULL) {
		destroy_world(client->world);
		client->world = create_world();
		(*client->next_scene)(client->world);
		client->next_scene = NULL;
		client->resized = true;
	} else {
		client->resized = false;
	}
}

void client_input_reset(struct client* client)
{
	client->input_delta = (const struct input_state){0};
}
