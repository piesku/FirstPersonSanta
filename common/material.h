#pragma once

#include "gl.h"

struct layout_colored_unlit {
	// Uniforms
	GLint pv;
	GLint world;
	GLint self;
	GLint color;
	// Attributes
	GLint vertex_position;
	GLint vertex_normal;
};

struct layout_colored_diffuse {
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

struct layout_textured_unlit {
	// Uniforms
	GLint pv;
	GLint world;
	GLint self;
	GLint color;
	GLint sampler;
	GLint texscale;
	// Attributes
	GLint vertex_position;
	GLint vertex_normal;
	GLint vertex_texcoord;
};

struct layout_postprocess {
	// Uniforms
	GLint dimensions;
	GLint eye_world;
	GLint eye_unprojection;
	GLint color_map;
	GLint normal_map;
	GLint depth_map;
	GLint light_positions;
	GLint light_colors;
	GLint light_directions;
	// Attributes
	GLint vertex_position;
	GLint vertex_texcoord;
};

struct material {
	GLenum mode;
	GLuint program;
	union {
		struct layout_colored_unlit colored_unlit;
		struct layout_colored_diffuse colored_diffuse;
		struct layout_textured_unlit textured_unlit;
		struct layout_postprocess postprocess;
	} layout;
};

GLuint create_program(
		const GLchar* vertex_shader_source,
		const GLchar* fragment_shader_source);
