#include <stdint.h>
#include <stdlib.h>

#include "client.h"
#include "com_camera.h"
#include "com_render.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_RENDER;

static inline void use_basic_colored(struct client* client, RenderBasicColored* render)
{
	struct material material = client->materials[render->material];

	glUseProgram(material.program);
	glUniformMatrix4fv(material.layout.basic_colored.pv, 1, GL_FALSE, client->camera->pv);
}

static inline void draw_basic_colored(struct client* client, Transform* transform, RenderBasicColored* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];

	glUniformMatrix4fv(material.layout.basic_colored.world, 1, GL_FALSE, transform->world);
	glUniform4fv(material.layout.basic_colored.color, 1, render->color);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.basic_colored.vertex_position);
	glVertexAttribPointer(material.layout.basic_colored.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

static inline void use_basic_textured(struct client* client, RenderBasicTextured* render)
{
	struct material material = client->materials[render->material];

	glUseProgram(material.program);
	glUniformMatrix4fv(material.layout.basic_textured.pv, 1, GL_FALSE, client->camera->pv);
}

static inline void draw_basic_textured(struct client* client, Transform* transform, RenderBasicTextured* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];
	GLuint texture = client->assets[render->texture];

	glUniformMatrix4fv(material.layout.basic_textured.world, 1, GL_FALSE, transform->world);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(material.layout.basic_textured.sampler, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.basic_textured.vertex_position);
	glVertexAttribPointer(material.layout.basic_textured.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.texcoord_buffer);
	glEnableVertexAttribArray(material.layout.basic_textured.vertex_texcoord);
	glVertexAttribPointer(material.layout.basic_textured.vertex_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

static inline void use_diffuse(struct client* client, RenderDiffuse* render)
{
	struct material material = client->materials[render->material];

	glUseProgram(material.program);
	glUniformMatrix4fv(material.layout.diffuse.pv, 1, GL_FALSE, client->camera->pv);
	glUniform4fv(material.layout.diffuse.light_positions, 1, client->lights.positions);
	glUniform4fv(material.layout.diffuse.light_details, 1, client->lights.details);
}

static inline void draw_diffuse(struct client* client, Transform* transform, RenderDiffuse* render)
{
	struct mesh mesh = client->meshes[render->mesh];
	struct material material = client->materials[render->material];

	glUniformMatrix4fv(material.layout.diffuse.world, 1, GL_FALSE, transform->world);
	glUniformMatrix4fv(material.layout.diffuse.self, 1, GL_FALSE, transform->self);
	glUniform4fv(material.layout.diffuse.color, 1, render->color);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glEnableVertexAttribArray(material.layout.diffuse.vertex_position);
	glVertexAttribPointer(material.layout.diffuse.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
	glEnableVertexAttribArray(material.layout.diffuse.vertex_normal);
	glVertexAttribPointer(material.layout.diffuse.vertex_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glDrawElements(material.mode, mesh.index_count, GL_UNSIGNED_SHORT, 0);
}

void sys_render(struct client* client, struct world* world)
{
	if (client->camera == NULL) {
		return;
	}

	if (client->resized) {
		glViewport(0, 0, client->width, client->height);
	}

	glClearColor(0.9, 0.9, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Transform* transform = world->transform[i];
			Render* render = world->render[i];

			switch (render->kind) {
				case RENDER_BASIC_COLORED:
					use_basic_colored(client, &render->basic_colored);
					draw_basic_colored(client, transform, &render->basic_colored);
					break;
				case RENDER_BASIC_TEXTURED:
					use_basic_textured(client, &render->basic_textured);
					draw_basic_textured(client, transform, &render->basic_textured);
					break;
				case RENDER_DIFFUSE:
					use_diffuse(client, &render->diffuse);
					draw_diffuse(client, transform, &render->diffuse);
					break;
			}
		}
	}
}
