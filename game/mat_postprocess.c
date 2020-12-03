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

			"vec4 normal_depth_at(vec2 uv) {"
			"	vec4 normal = texture(normal_map, uv);"
			"	vec4 depth = texture(depth_map, uv);"
			"	return vec4(normal.xyz, depth.x);"
			"}"

			"void main() {"
			"	vec4 color = texture(color_map, vert_texcoord);"

			"	vec4 current = normal_depth_at(vert_texcoord);"
			"	vec2 offsets[8] = {"
			"			vec2(-1, -1), vec2(-1, 0), vec2(-1, 1),"
			"			vec2(0, -1), vec2(0, 1),"
			"			vec2(1, -1), vec2(1, 0), vec2(1, 1)};"
			"	vec4 sampled = vec4(0.0);"
			"	for (int j = 0; j < 8; j++) {"
			"		sampled += normal_depth_at(vert_texcoord + offsets[j] * 0.001);"
			"	}"
			"	sampled /= 8.0;"

			"	frag_color = mix(color, vec4(0.0, 0.0, 0.0, 1.0), step(0.01, length(current - sampled)));"
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
