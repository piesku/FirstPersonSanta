#include "../common/material.h"

struct material mat_postprocess(void)
{
	GLchar vertex_shader_source[] =
			"#version 330\n"

			"in vec3 position;"
			"in vec2 texcoord;"
			"out vec2 vert_texcoord;"

			"void main() {"
			"  	 gl_Position = vec4(position, 1.0);"
			"  	 vert_texcoord = texcoord;"
			"}";

	GLchar fragment_shader_source[] =
			"#version 330\n"
			"precision mediump float;"

			"uniform sampler2D color_map;"
			"uniform sampler2D normal_map;"
			"uniform sampler2D depth_map;"

			"in vec2 vert_texcoord;"
			"out vec4 frag_color;"

			"void main() {"
			"    frag_color = texture(color_map, vert_texcoord);"
			"}";

	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.postprocess =
					(struct layout_postprocess){
							.color_map = glGetUniformLocation(program, "color_map"),
							.normal_map = glGetUniformLocation(program, "normal_map"),
							.depth_map = glGetUniformLocation(program, "depth_map"),
							.vertex_position = glGetAttribLocation(program, "position"),
							.vertex_texcoord = glGetAttribLocation(program, "texcoord"),
					},
	};

	return material;
}
