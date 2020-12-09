#include "mesh.h"

#include <cgltf.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl.h"

struct mesh mesh_load(const char* path)
{
	struct mesh mesh = {0};

	cgltf_options options = {0};
	cgltf_data* data = NULL;

	{
		cgltf_result result = cgltf_parse_file(&options, path, &data);
		if (result != cgltf_result_success) {
			printf("Failed to load model %s (error %d)", path, result);
			exit(1);
		}
	}

	{
		cgltf_result result = cgltf_load_buffers(&options, data, path);
		if (result != cgltf_result_success) {
			printf("Failed to load buffers of model %s (error %d)", path, result);
			exit(1);
		}
	}

	if (data->meshes_count != 1) {
		printf("Model %s contains more than one mesh", path);
		exit(1);
	}

	cgltf_mesh* first_mesh = &data->meshes[0];

	if (first_mesh->primitives_count == 0) {
		// TODO Handle multiple primitives.
		printf("Model %s doesn't contain any primitives", path);
		exit(1);
	}

	cgltf_primitive* first_primitive = &first_mesh->primitives[0];

	{
		cgltf_accessor* indices = first_primitive->indices;
		cgltf_buffer_view* view = indices->buffer_view;

		glGenBuffers(1, &mesh.index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->size, (GLbyte*)view->buffer->data + view->offset, GL_STATIC_DRAW);
		mesh.index_count = (GLuint)indices->count;
	}

	for (int i = 0; i < first_primitive->attributes_count; i++) {
		cgltf_attribute* attr = &first_primitive->attributes[i];
		switch (attr->type) {
			case cgltf_attribute_type_position: {
				cgltf_buffer_view* view = attr->data->buffer_view;
				glGenBuffers(1, &mesh.vertex_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
				glBufferData(GL_ARRAY_BUFFER, view->size, (GLbyte*)view->buffer->data + view->offset, GL_STATIC_DRAW);
				break;
			}
			case cgltf_attribute_type_normal: {
				cgltf_buffer_view* view = attr->data->buffer_view;
				glGenBuffers(1, &mesh.normal_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
				glBufferData(GL_ARRAY_BUFFER, view->size, (GLbyte*)view->buffer->data + view->offset, GL_STATIC_DRAW);
				break;
			}
			case cgltf_attribute_type_texcoord: {
				cgltf_buffer_view* view = attr->data->buffer_view;
				glGenBuffers(1, &mesh.texcoord_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.texcoord_buffer);
				glBufferData(GL_ARRAY_BUFFER, view->size, (GLbyte*)view->buffer->data + view->offset, GL_STATIC_DRAW);
				break;
			}
		}
	}

	cgltf_free(data);

	return mesh;
}
