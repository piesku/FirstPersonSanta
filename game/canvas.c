#include "canvas.h"

#include <stdlib.h>
#include <string.h>

#include "../common/matrix.h"

struct material mat_basic_colored(void);
struct material mat_basic_textured(void);
struct material mat_diffuse_gouraud(void);

struct mesh mesh_cube(void);

void sys_camera(struct canvas* canvas, struct world* world);
void sys_control_keyboard(struct canvas* canvas, struct world* world, float delta);
void sys_light(struct canvas* canvas, struct world* world);
void sys_move(struct canvas* canvas, struct world* world, float delta);
void sys_render(struct canvas* canvas, struct world* world);
void sys_transform(struct canvas* canvas, struct world* world, float delta);


void canvas_setup(struct canvas* canvas, int32_t width, int32_t height)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glViewport(0, 0, width, height);

	canvas->width = width;
	canvas->height = height;
	canvas->resized = true;

	canvas->materials[MAT_BASIC_COLORED] = mat_basic_colored();
	canvas->meshes[MESH_CUBE] = mesh_cube();

	canvas->camera = NULL;
}

void canvas_resize(struct canvas* canvas, int32_t width, int32_t height)
{
	canvas->width = width;
	canvas->height = height;
	canvas->resized = true;
}

void canvas_teardown(struct canvas* canvas)
{
	for (int8_t i = 0; i < MATERIALS_LENGTH; i++) {
		glDeleteProgram(canvas->materials[i].program);
	}
	for (int8_t i = 0; i < MESHES_LENGTH; i++) {
		glDeleteBuffers(1, &canvas->meshes[i].vertex_buffer);
		glDeleteBuffers(1, &canvas->meshes[i].index_buffer);
	}
}

void canvas_world_update(struct canvas* canvas, struct world* world, float delta)
{
	sys_control_keyboard(canvas, world, delta);
	sys_move(canvas, world, delta);
	sys_transform(canvas, world, delta);
}

void canvas_frame_update(struct canvas* canvas, struct world* world)
{
	sys_camera(canvas, world);
	sys_light(canvas, world);
	sys_render(canvas, world);

	canvas->resized = false;
}

void canvas_input_reset(struct canvas* canvas)
{
	canvas->input_delta = (const struct input_state){0};
}
