#include <stdint.h>
#include <stdlib.h>

#include "client.h"
#include "com_camera.h"
#include "com_render.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_RENDER;

static inline void use_colored_unlit(struct client* client, RenderColoredUnlit* render)
{
	struct material material = client->materials[render->material];

	glUseProgram(material.program);
	glUniformMatrix4fv(material.layout.colored_unlit.pv, 1, GL_FALSE, client->camera->pv);
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

static inline void use_colored_diffuse(struct client* client, RenderColoredDiffuse* render)
{
	struct material material = client->materials[render->material];

	glUseProgram(material.program);
	glUniformMatrix4fv(material.layout.colored_diffuse.pv, 1, GL_FALSE, client->camera->pv);
	glUniform4fv(material.layout.colored_diffuse.light_positions, 1, client->lights.positions);
	glUniform4fv(material.layout.colored_diffuse.light_details, 1, client->lights.details);
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

static inline void use_textured_unlit(struct client* client, RenderTexturedUnlit* render)
{
	struct material material = client->materials[render->material];

	glUseProgram(material.program);
	glUniformMatrix4fv(material.layout.textured_unlit.pv, 1, GL_FALSE, client->camera->pv);
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
				case RENDER_COLORED_UNLIT:
					use_colored_unlit(client, &render->colored_unlit);

					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glLineWidth(10.0f);

					RenderColoredUnlit outline = render->colored_unlit;
					outline.color[0] = 0;
					outline.color[1] = 0;
					outline.color[2] = 0;
					outline.color[3] = 1;

					draw_colored_unlit(client, transform, &outline);

					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glEnable(GL_POLYGON_OFFSET_FILL);
					glPolygonOffset(1.0, 1.0);
					draw_colored_unlit(client, transform, &render->colored_unlit);
					glDisable(GL_POLYGON_OFFSET_FILL);

					break;
				case RENDER_COLORED_DIFFUSE:
					use_colored_diffuse(client, &render->colored_diffuse);
					draw_colored_diffuse(client, transform, &render->colored_diffuse);
					break;
				case RENDER_TEXTURED_UNLIT:
					use_textured_unlit(client, &render->textured_unlit);
					draw_textured_unlit(client, transform, &render->textured_unlit);
					break;
			}
		}
	}
}
