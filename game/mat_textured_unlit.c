#include "../common/material.h"

struct material mat_textured_unlit(void)
{
	GLchar vertex_shader_source[] =
			"#version 330\n"

			"uniform mat4 pv;"
			"uniform mat4 world;"
			"uniform mat4 self;"

			"in vec3 position;"
			"in vec3 normal;"
			"in vec2 texcoord;"

			"out vec2 vert_texcoord;"
			"out vec3 vert_normal;"

			"void main() {"
			"    gl_Position = pv * world * vec4(position, 1.0);"
			"    vert_normal = normalize((vec4(normal, 1.0) * self).xyz);"
			"  	 vert_texcoord = texcoord;"
			"}";
	GLchar fragment_shader_source[] =
			"#version 330\n"
			"precision mediump float;"

			"uniform vec4 color;"
			"uniform sampler2D sampler;"
			"uniform vec2 texscale;"

			"in vec2 vert_texcoord;"
			"in vec3 vert_normal;"

			"layout(location = 0) out vec4 frag_color;"
			"layout(location = 1) out vec3 frag_normal;"

			"void main() {"
			"    frag_color = color * texture(sampler, vert_texcoord * texscale);"
			"    frag_normal = vert_normal * 0.5 + vec3(0.5);"
			"}";
	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.textured_unlit =
					(struct layout_textured_unlit){
							.pv = glGetUniformLocation(program, "pv"),
							.world = glGetUniformLocation(program, "world"),
							.self = glGetUniformLocation(program, "self"),
							.color = glGetUniformLocation(program, "color"),
							.sampler = glGetUniformLocation(program, "sampler"),
							.texscale = glGetUniformLocation(program, "texscale"),
							.vertex_position = glGetAttribLocation(program, "position"),
							.vertex_normal = glGetAttribLocation(program, "normal"),
							.vertex_texcoord = glGetAttribLocation(program, "texcoord"),
					},
	};
	return material;
}
