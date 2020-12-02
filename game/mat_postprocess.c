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

			"uniform sampler2D sampler;"

			"in vec2 vert_texcoord;"
			"out vec4 frag_color;"

			"void main() {"
			"    frag_color = texture(sampler, vert_texcoord);"
			"    frag_color = frag_color * vec4(1.0, 0.0, 0.0, 1.0);"
			"}";

	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.postprocess =
					(struct layout_postprocess){
							.sampler = glGetUniformLocation(program, "sampler"),
							.vertex_position = glGetAttribLocation(program, "position"),
							.vertex_texcoord = glGetAttribLocation(program, "texcoord"),
					},
	};

	return material;
}
