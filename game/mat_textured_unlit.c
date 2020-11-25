#include "../common/material.h"

struct material mat_textured_unlit(void)
{
	GLchar vertex_shader_source[] =
			"#version 330\n"
			"uniform mat4 pv;"
			"uniform mat4 world;"
			"in vec3 position;"
			"in vec2 texcoord;"
			"out vec2 vert_texcoord;"
			"void main() {"
			"  	 gl_Position = pv * world * vec4(position, 1.0);"
			"  	 vert_texcoord = texcoord;"
			"}";
	GLchar fragment_shader_source[] =
			"#version 330\n"
			"precision mediump float;"
			"uniform sampler2D sampler;"
			"in vec2 vert_texcoord;"
			"out vec4 frag_color;"
			"void main() {"
			"    frag_color = texture(sampler, vert_texcoord);"
			"}";
	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.textured_unlit =
					(struct layout_textured_unlit){
							.pv = glGetUniformLocation(program, "pv"),
							.world = glGetUniformLocation(program, "world"),
							.sampler = glGetUniformLocation(program, "sampler"),
							.vertex_position = glGetAttribLocation(program, "position"),
							.vertex_texcoord = glGetAttribLocation(program, "texcoord"),
					},
	};
	return material;
}
