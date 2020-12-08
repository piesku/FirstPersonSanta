#include <stdint.h>

#include "../common/gl.h"
#include "../common/material.h"

#include "client.h"
#include "com_camera.h"
#include "index.h"

void sys_postprocess(struct client* client)
{
	if (client->camera_default->kind != CAMERA_FRAMEBUFFER) {
		// The default camera renders directly to the screen.
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, client->width, client->height);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	struct eye* eye = &client->camera_default->framebuffer.eye;
	struct material* material = &client->materials[MAT_POSTPROCESS];
	struct layout_postprocess* layout = &material->layout.postprocess;
	struct mesh* mesh = &client->meshes[MESH_QUAD];

	glUseProgram(material->program);
	glUniform2f(layout->dimensions, (GLfloat)client->width, (GLfloat)client->height);
	glUniformMatrix4fv(layout->eye_world, 1, GL_FALSE, (const GLfloat*)&eye->world);
	glUniformMatrix4fv(layout->eye_unprojection, 1, GL_FALSE, (const GLfloat*)&eye->unprojection);
	glUniform4fv(layout->light_positions, 8, client->lights.positions);
	glUniform4fv(layout->light_details, 8, client->lights.details);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, client->textures[TEX_RENDER_RGBA]);
	glUniform1i(layout->color_map, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, client->textures[TEX_RENDER_NORMALS]);
	glUniform1i(layout->normal_map, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, client->textures[TEX_RENDER_DEPTH]);
	glUniform1i(layout->depth_map, 2);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
	glEnableVertexAttribArray(layout->vertex_position);
	glVertexAttribPointer(layout->vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->texcoord_buffer);
	glEnableVertexAttribArray(layout->vertex_texcoord);
	glVertexAttribPointer(layout->vertex_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer);
	glDrawElements(material->mode, mesh->index_count, GL_UNSIGNED_SHORT, 0);
}
