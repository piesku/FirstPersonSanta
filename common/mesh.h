#pragma once

#include "gl.h"

struct mesh {
	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint texcoord_buffer;
	GLuint index_buffer;
	GLuint index_count;
};

struct mesh mesh_load(const char* path);
