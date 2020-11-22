#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

struct mesh {
	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint texcoord_buffer;
	GLuint index_buffer;
	GLuint index_count;
};
