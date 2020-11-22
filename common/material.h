#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

struct layout_basic_colored {
	// Uniforms
	GLint pv;
	GLint world;
	GLint color;
	// Attributes
	GLint vertex_position;
};

struct layout_basic_textured {
	// Uniforms
	GLint pv;
	GLint world;
	GLint sampler;
	// Attributes
	GLint vertex_position;
	GLint vertex_texcoord;
};

struct layout_diffuse {
	// Uniforms
	GLint pv;
	GLint world;
	GLint self;
	GLint color;
	GLint light_positions;
	GLint light_details;
	// Attributes
	GLint vertex_position;
	GLint vertex_normal;
};

struct layout_text_bitmap {
	// Uniforms
	GLint sampler;
	// Attributes
	GLint vertex_position;
	GLint vertex_texcoord;
};

struct material {
	GLenum mode;
	GLuint program;
	union {
		struct layout_basic_colored basic_colored;
		struct layout_basic_textured basic_textured;
		struct layout_diffuse diffuse;
		struct layout_text_bitmap text_bitmap;
	} layout;
};

GLuint create_program(const GLchar* vertex_shader_source, const GLchar* fragment_shader_source);
