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
	glUniformMatrix4fv(material->layout.colored_unlit.pv, 1, GL_FALSE, eye->pv);
}

static inline void draw_colored_unlit(struct client* client, Transform* transform, RenderColoredUnlit* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];

	glUniformMatrix4fv(material.layout.colored_unlit.world, 1, GL_FALSE, transform->world);
	glUniform4fv(material.layout.colored_unlit.color, 1, render->color);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.colored_unlit.vertex_position);
	glVertexAttribPointer(material.layout.colored_unlit.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

static inline void use_colored_diffuse(struct client* client, struct material* material, struct eye* eye)
{
	glUseProgram(material->program);
	glUniformMatrix4fv(material->layout.colored_diffuse.pv, 1, GL_FALSE, eye->pv);
	glUniform4fv(material->layout.colored_diffuse.light_positions, 1, client->lights.positions);
	glUniform4fv(material->layout.colored_diffuse.light_details, 1, client->lights.details);
}

static inline void draw_colored_diffuse(struct client* client, Transform* transform, RenderColoredDiffuse* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];

	glUniformMatrix4fv(material.layout.colored_diffuse.world, 1, GL_FALSE, transform->world);
	glUniformMatrix4fv(material.layout.colored_diffuse.self, 1, GL_FALSE, transform->self);
	glUniform4fv(material.layout.colored_diffuse.color, 1, render->color);

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
	glUniformMatrix4fv(material->layout.textured_unlit.pv, 1, GL_FALSE, eye->pv);
}

static inline void draw_textured_unlit(struct client* client, Transform* transform, RenderTexturedUnlit* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];
	GLuint texture = client->textures[render->texture];

	glUniformMatrix4fv(material.layout.textured_unlit.world, 1, GL_FALSE, transform->world);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(material.layout.textured_unlit.sampler, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.textured_unlit.vertex_position);
	glVertexAttribPointer(material.layout.textured_unlit.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.texcoord_buffer);
	glEnableVertexAttribArray(material.layout.textured_unlit.vertex_texcoord);
	glVertexAttribPointer(material.layout.textured_unlit.vertex_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

void render(struct client* client, struct world* world, struct eye* eye)
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


void sys_render(struct client* client, struct world* world)
{
	if (client->cameras[0] != NULL) {
		// Render to display.
		CameraDisplay* camera = client->cameras[0];
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		glViewport(0, 0, client->width, client->height);
		glClearColor(
				camera->clear_color[0],
				camera->clear_color[1],
				camera->clear_color[2],
				camera->clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(client, world, &camera->eye);
	}

	if (client->cameras[1] != NULL) {
		// Render to framebuffer.
		CameraFramebuffer* camera = client->cameras[1];
		glBindFramebuffer(GL_FRAMEBUFFER, camera->target);
		glViewport(0, 0, camera->width, camera->height);
		glClearColor(
				camera->clear_color[0],
				camera->clear_color[1],
				camera->clear_color[2],
				camera->clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(client, world, &camera->eye);
	}

}
