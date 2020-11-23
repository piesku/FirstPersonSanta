#include "../common/material.h"

struct material mat_basic_colored(void)
{
	GLchar vertex_shader_source[] =
			"#version 330\n"
			"uniform mat4 pv;"
			"uniform mat4 world;"
			"in vec3 position;"
			"void main() {"
			"  	 gl_Position = pv * world * vec4(position, 1.0);"
			"}";
	GLchar fragment_shader_source[] =
			"#version 330\n"
			"precision mediump float;"
			"uniform vec4 color;"
			"out vec4 frag_color;"
			"void main() {"
			"    frag_color = color;"
			"}";
	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.basic_colored =
					(struct layout_basic_colored){
							.pv = glGetUniformLocation(program, "pv"),
							.world = glGetUniformLocation(program, "world"),
							.color = glGetUniformLocation(program, "color"),
							.vertex_position = glGetAttribLocation(program, "position"),
					},
	};
	return material;
}
