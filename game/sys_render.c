#include <stdint.h>
#include <stdlib.h>

#include "../common/gl.h"
#include "../common/material.h"

#include "client.h"
#include "com_camera.h"
#include "com_render.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_RENDER;

static inline void use_colored_unlit(struct client* client, struct material* material, struct eye* eye)
{
	glUseProgram(material->program);
	glUniformMatrix4fv(material->layout.colored_unlit.pv, 1, GL_FALSE, (const GLfloat*)&eye->pv);
}

static inline void draw_colored_unlit(struct client* client, Transform* transform, RenderColoredUnlit* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];

	glUniformMatrix4fv(material.layout.colored_unlit.world, 1, GL_FALSE, (const GLfloat*)&transform->world);
	glUniformMatrix4fv(material.layout.colored_unlit.self, 1, GL_FALSE, (const GLfloat*)&transform->self);
	glUniform4fv(material.layout.colored_unlit.color, 1, (const GLfloat*)&render->color);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.colored_unlit.vertex_position);
	glVertexAttribPointer(material.layout.colored_unlit.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
	glEnableVertexAttribArray(material.layout.colored_unlit.vertex_normal);
	glVertexAttribPointer(material.layout.colored_unlit.vertex_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

static inline void use_colored_diffuse(struct client* client, struct material* material, struct eye* eye)
{
	glUseProgram(material->program);
	glUniformMatrix4fv(material->layout.colored_diffuse.pv, 1, GL_FALSE, (const GLfloat*)&eye->pv);
	glUniform4fv(material->layout.colored_diffuse.light_positions, 1, client->lights.positions);
	glUniform4fv(material->layout.colored_diffuse.light_details, 1, client->lights.details);
}

static inline void draw_colored_diffuse(struct client* client, Transform* transform, RenderColoredDiffuse* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];

	glUniformMatrix4fv(material.layout.colored_diffuse.world, 1, GL_FALSE, (const GLfloat*)&transform->world);
	glUniformMatrix4fv(material.layout.colored_diffuse.self, 1, GL_FALSE, (const GLfloat*)&transform->self);
	glUniform4fv(material.layout.colored_diffuse.color, 1, (const GLfloat*)&render->color);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.colored_diffuse.vertex_position);
	glVertexAttribPointer(material.layout.colored_diffuse.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
	glEnableVertexAttribArray(material.layout.colored_diffuse.vertex_normal);
	glVertexAttribPointer(material.layout.colored_diffuse.vertex_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

static inline void use_textured_unlit(struct client* client, struct material* material, struct eye* eye)
{
	glUseProgram(material->program);
	glUniformMatrix4fv(material->layout.textured_unlit.pv, 1, GL_FALSE, (const GLfloat*)&eye->pv);
}

static inline void draw_textured_unlit(struct client* client, Transform* transform, RenderTexturedUnlit* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];
	GLuint texture = client->textures[render->texture];

	glUniformMatrix4fv(material.layout.textured_unlit.world, 1, GL_FALSE, (const GLfloat*)&transform->world);
	glUniformMatrix4fv(material.layout.textured_unlit.self, 1, GL_FALSE, (const GLfloat*)&transform->self);
	glUniform4fv(material.layout.textured_unlit.color, 1, (const GLfloat*)&render->color);
	glUniform2fv(material.layout.textured_unlit.texscale, 1, (const GLfloat*)&render->texscale);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(material.layout.textured_unlit.sampler, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.textured_unlit.vertex_position);
	glVertexAttribPointer(material.layout.textured_unlit.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.texcoord_buffer);
	glEnableVertexAttribArray(material.layout.textured_unlit.vertex_texcoord);
	glVertexAttribPointer(material.layout.textured_unlit.vertex_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
	glEnableVertexAttribArray(material.layout.textured_unlit.vertex_normal);
	glVertexAttribPointer(material.layout.textured_unlit.vertex_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

static void render_world(struct client* client, struct world* world, struct eye* eye)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Transform* transform = world->transform[i];
			Render* render = world->render[i];

			switch (render->kind) {
				case RENDER_COLORED_UNLIT: {
					struct material* material = &client->materials[render->colored_unlit.material];
					use_colored_unlit(client, material, eye);
					draw_colored_unlit(client, transform, &render->colored_unlit);
					break;
				}
				case RENDER_COLORED_DIFFUSE: {
					struct material* material = &client->materials[render->colored_diffuse.material];
					use_colored_diffuse(client, material, eye);
					draw_colored_diffuse(client, transform, &render->colored_diffuse);
					break;
				}
				case RENDER_TEXTURED_UNLIT: {
					struct material* material = &client->materials[render->textured_unlit.material];
					use_textured_unlit(client, material, eye);
					draw_textured_unlit(client, transform, &render->textured_unlit);
					break;
				}
			}
		}
	}
}

static void render_display(struct client* client, struct world* world, CameraDisplay* camera)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, client->width, client->height);
	glClearColor(
			camera->clear_color.x,
			camera->clear_color.y,
			camera->clear_color.z,
			camera->clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render_world(client, world, &camera->eye);
}

static void render_framebuffer(struct client* client, struct world* world, CameraFramebuffer* camera)
{
	struct render_target* target = &client->targets[camera->target];
	glBindFramebuffer(GL_FRAMEBUFFER, target->framebuffer);
	glViewport(0, 0, target->width, target->height);
	glClearColor(
			camera->clear_color.x,
			camera->clear_color.y,
			camera->clear_color.z,
			camera->clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render_world(client, world, &camera->eye);
}

void sys_render(struct client* client, struct world* world)
{
	if (client->camera_default != NULL) {
		switch (client->camera_default->kind) {
			case CAMERA_DISPLAY:
				render_display(client, world, &client->camera_default->display);
				break;
			case CAMERA_FRAMEBUFFER:
				render_framebuffer(client, world, &client->camera_default->framebuffer);
				break;
		}
	}

	if (client->camera_minimap != NULL) {
		render_framebuffer(client, world, client->camera_minimap);
	}
}
