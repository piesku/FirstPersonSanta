#pragma once

#include "gl.h"

struct mesh {
	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint texcoord_buffer;
	GLuint index_buffer;
	GLuint index_count;
};

void load_scene_from_gltf(struct mesh* mesh, const char* file_location);
