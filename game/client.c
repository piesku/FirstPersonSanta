#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/matrix.h"
#include "../common/mesh.h"
#include "../common/texture.h"

#include "world.h"

struct material mat_colored_unlit(void);
struct material mat_textured_unlit(void);
struct material mat_postprocess(void);

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
	client->meshes[MESH_BEAR] = mesh_load("models/bear.glb");
	client->meshes[MESH_BED_BUNK] = mesh_load("models/bed_bunk.glb");
	client->meshes[MESH_BED_DOUBLE] = mesh_load("models/bed_double.glb");
	client->meshes[MESH_BED_SINGLE] = mesh_load("models/bed_single.glb");
	client->meshes[MESH_BENCH] = mesh_load("models/bench.glb");
	client->meshes[MESH_BOOKCASE_CLOSED] = mesh_load("models/bookcase_closed.glb");
	client->meshes[MESH_BOOKCASE_CLOSED_DOORS] = mesh_load("models/bookcase_closed_doors.glb");
	client->meshes[MESH_BOOKCASE_CLOSED_WIDE] = mesh_load("models/bookcase_closed_wide.glb");
	client->meshes[MESH_BOOKCASE_OPEN] = mesh_load("models/bookcase_open.glb");
	client->meshes[MESH_BOOKS] = mesh_load("models/books.glb");
	client->meshes[MESH_CABINET_BED] = mesh_load("models/cabinet_bed.glb");
	client->meshes[MESH_CABINET_BED_DRAWER] = mesh_load("models/cabinet_bed_drawer.glb");
	client->meshes[MESH_CABINET_BED_DRAWER_TABLE] = mesh_load("models/cabinet_bed_drawer_table.glb");
	client->meshes[MESH_CABINET_TELEVISION] = mesh_load("models/cabinet_television.glb");
	client->meshes[MESH_CABINET_TELEVISION_DOORS] = mesh_load("models/cabinet_television_doors.glb");
	client->meshes[MESH_CARDBOARD_BOX_CLOSED] = mesh_load("models/cardboard_box_closed.glb");
	client->meshes[MESH_CARDBOARD_BOX_OPEN] = mesh_load("models/cardboard_box_open.glb");
	client->meshes[MESH_CHAIR] = mesh_load("models/chair.glb");
	client->meshes[MESH_CHAIR_ROUNDED] = mesh_load("models/chair_rounded.glb");
	client->meshes[MESH_COAT_RACK] = mesh_load("models/coat_rack.glb");
	client->meshes[MESH_COAT_RACK_STANDING] = mesh_load("models/coat_rack_standing.glb");
	client->meshes[MESH_COMPUTER_SCREEN] = mesh_load("models/computer_screen.glb");
	client->meshes[MESH_CUBE] = mesh_load("models/cube.glb");
	client->meshes[MESH_DESK] = mesh_load("models/desk.glb");
	client->meshes[MESH_GIFT] = mesh_load("models/gift.glb");
	client->meshes[MESH_LAMP_ROUND_FLOOR] = mesh_load("models/lamp_round_floor.glb");
	client->meshes[MESH_LAMP_ROUND_TABLE] = mesh_load("models/lamp_round_table.glb");
	client->meshes[MESH_LOUNGE_CHAIR] = mesh_load("models/lounge_chair.glb");
	client->meshes[MESH_LOUNGE_SOFA] = mesh_load("models/lounge_sofa.glb");
	client->meshes[MESH_MONKEY] = mesh_load("models/monkey.glb");
	client->meshes[MESH_PLANT_SMALL_1] = mesh_load("models/plant_small_1.glb");
	client->meshes[MESH_PLANT_SMALL_2] = mesh_load("models/plant_small_2.glb");
	client->meshes[MESH_PLANT_SMALL_3] = mesh_load("models/plant_small_3.glb");
	client->meshes[MESH_POTTED_PLANT] = mesh_load("models/potted_plant.glb");
	client->meshes[MESH_QUAD] = mesh_load("models/quad.glb");
	client->meshes[MESH_RADIO] = mesh_load("models/radio.glb");
	client->meshes[MESH_SIDE_TABLE] = mesh_load("models/side_table.glb");
	client->meshes[MESH_SIDE_TABLE_DRAWERS] = mesh_load("models/side_table_drawers.glb");
	client->meshes[MESH_STOOL_BAR_SQUARE] = mesh_load("models/stool_bar_square.glb");
	client->meshes[MESH_TABLE] = mesh_load("models/table.glb");
	client->meshes[MESH_TABLE_COFFEE] = mesh_load("models/table_coffee.glb");
	client->meshes[MESH_TABLE_COFFEE_SQUARE] = mesh_load("models/table_coffee_square.glb");
	client->meshes[MESH_TABLE_ROUND] = mesh_load("models/table_round.glb");
	client->meshes[MESH_TELEVISION_MODERN] = mesh_load("models/television_modern.glb");
	client->meshes[MESH_TELEVISION_VINTAGE] = mesh_load("models/television_vintage.glb");
	client->meshes[MESH_WALL] = mesh_load("models/wall.glb");
	client->meshes[MESH_WALL_DOORWAY] = mesh_load("models/wall_doorway.glb");
	client->meshes[MESH_WALL_WINDOW] = mesh_load("models/wall_window.glb");

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
	sys_render(client, world);
	sys_light(client, world);
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
