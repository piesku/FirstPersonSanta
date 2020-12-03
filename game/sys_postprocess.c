#include <stdint.h>
#include <stdlib.h>

#include "../common/gl.h"
#include "../common/material.h"

#include "client.h"
#include "com_camera.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

void sys_postprocess(struct client* client, struct world* world)
{
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	glViewport(0, 0, client->width, client->height);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	struct material* material = &client->materials[MAT_POSTPROCESS];
	struct mesh* mesh = &client->meshes[MESH_QUAD];

	glUseProgram(material->program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, client->textures[TEX_RENDER_RGBA]);
	glUniform1i(material->layout.postprocess.color_map, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, client->textures[TEX_RENDER_NORMALS]);
	glUniform1i(material->layout.postprocess.normal_map, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, client->textures[TEX_RENDER_DEPTH]);
	glUniform1i(material->layout.postprocess.depth_map, 2);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
	glEnableVertexAttribArray(material->layout.postprocess.vertex_position);
	glVertexAttribPointer(material->layout.postprocess.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->texcoord_buffer);
	glEnableVertexAttribArray(material->layout.postprocess.vertex_texcoord);
	glVertexAttribPointer(material->layout.postprocess.vertex_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer);
	glDrawElements(material->mode, mesh->index_count, GL_UNSIGNED_SHORT, 0);
}
