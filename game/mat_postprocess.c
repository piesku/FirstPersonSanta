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

			"uniform vec2 dimensions;"
			"uniform sampler2D color_map;"
			"uniform sampler2D normal_map;"
			"uniform sampler2D depth_map;"

			"in vec2 vert_texcoord;"
			"out vec4 frag_color;"

			"const vec4 edge_color = vec4(0.0, 0.0, 0.0, 1.0);"

			"vec3 normal_at(vec2 uv) {"
			"	return texture(normal_map, uv).xyz * 2.0 - 1.0;"
			"}"

			"float depth_at(vec2 uv) {"
			"	return texture(depth_map, uv).x;"
			"}"

			"void main() {"
			"	vec4 current_color = texture(color_map, vert_texcoord);"
			"	vec3 current_normal = normal_at(vert_texcoord);"
			"	float current_depth = depth_at(vert_texcoord);"

			"	vec2 offsets[4] = {"
			"			vec2(-1, -1) / dimensions,"
			"			vec2(1, -1) / dimensions,"
			"			vec2(-1, 1) / dimensions,"
			"			vec2(1, 1) / dimensions,"
			"	};"

			"	vec3 n1 = normal_at(vert_texcoord + offsets[0])"
			"			- normal_at(vert_texcoord + offsets[3]);"
			"	vec3 n2 = normal_at(vert_texcoord + offsets[1])"
			"			- normal_at(vert_texcoord + offsets[2]);"
			"	float n = sqrt(dot(n1, n1) + dot(n2, n2));"

			"	if (n > 1.0) {"
			"		frag_color = edge_color;"
			"	} else {"
			"		float d1 = depth_at(vert_texcoord + offsets[0])"
			"				- depth_at(vert_texcoord + offsets[3]);"
			"		float d2 = depth_at(vert_texcoord + offsets[1])"
			"				- depth_at(vert_texcoord + offsets[2]);"
			"		float z = sqrt(d1 * d1 + d2 * d2);"
			"		frag_color = mix(current_color, edge_color, step(0.001, z));"
			"	}"
			"}";

	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.postprocess =
					(struct layout_postprocess){
							.dimensions = glGetUniformLocation(program, "dimensions"),
							.color_map = glGetUniformLocation(program, "color_map"),
							.normal_map = glGetUniformLocation(program, "normal_map"),
							.depth_map = glGetUniformLocation(program, "depth_map"),
							.vertex_position = glGetAttribLocation(program, "position"),
							.vertex_texcoord = glGetAttribLocation(program, "texcoord"),
					},
	};

	return material;
}
