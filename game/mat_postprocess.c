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

			"const int MAX_LIGHTS = 8;"

			"uniform vec2 dimensions;"
			"uniform mat4 eye_world;"
			"uniform mat4 eye_unprojection;"
			"uniform sampler2D color_map;"
			"uniform sampler2D normal_map;"
			"uniform sampler2D depth_map;"
			"uniform vec4 light_positions[MAX_LIGHTS];"
			"uniform vec4 light_colors[MAX_LIGHTS];"
			"uniform vec4 light_directions[MAX_LIGHTS];"

			"in vec2 vert_texcoord;"
			"out vec4 frag_color;"

			"const vec4 edge_color = vec4(0.0, 0.0, 0.0, 1.0);"

			"vec3 normal_at(vec2 uv) {"
			"	return texture(normal_map, uv).xyz * 2.0 - 1.0;"
			"}"

			"float depth_at(vec2 uv) {"
			"	return texture(depth_map, uv).x;"
			"}"

			"vec3 world_position_at(vec2 uv, float z) {"
			"	vec4 clip_position = vec4(uv * 2.0 - 1.0, z * 2.0 - 1.0, 1.0);"
			"	vec4 view_position = eye_unprojection * clip_position;"
			"	view_position /= view_position.w;"
			"	vec4 world_position = eye_world * view_position;"
			"	return world_position.xyz;"
			"}"

			"void main() {"
			"	vec4 current_color = texture(color_map, vert_texcoord);"
			"	vec3 current_normal = normal_at(vert_texcoord);"
			"	float current_depth = depth_at(vert_texcoord);"
			"	vec3 current_position = world_position_at(vert_texcoord, current_depth);"

			"	for (int i = 0; i < MAX_LIGHTS; i++) {"
			"		int light_kind = int(light_positions[i].w);"
			"		if (light_kind == 0) {"
			"			/* LIGHT_OFF */"
			"			break;"
			"		}"

			"		vec3 light_diff = light_positions[i].xyz - current_position;"
			"		float light_dist = length(light_diff);"
			"		float light_range = light_colors[i].a;"
			"		if (light_dist > light_range) {"
			"			continue;"
			"		}"

			"		vec3 light_normal = light_diff / light_dist;"
			"		float diffuse_factor = dot(current_normal, light_normal);"
			"		if (diffuse_factor < 0.0) {"
			"			continue;"
			"		}"

			"		if (light_kind == 2) {"
			"			/* LIGHT_SPOT */"
			"			vec3 light_forward = light_directions[i].xyz;"
			"			float light_angle = light_directions[i].w;"
			"			float current_cos = dot(light_forward, -light_normal);"
			"			if (current_cos < cos(light_angle / 2.0)) {"
			"				continue;"
			"			}"
			"		}"

			"		vec3 light_color = light_colors[i].rgb;"
			"		current_color = vec4(light_color, 1.0);"
			"	}"

			"	vec2 offsets[4] = vec2[]("
			"			vec2(-1, -1) / dimensions,"
			"			vec2(1, -1) / dimensions,"
			"			vec2(-1, 1) / dimensions,"
			"			vec2(1, 1) / dimensions"
			"	);"

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
			"		frag_color = mix(current_color, edge_color, step(0.01 / current_depth, z));"
			"	}"
			"}";

	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material){
			.mode = GL_TRIANGLES,
			.program = program,
			.layout.postprocess =
					(struct layout_postprocess){
							.dimensions = glGetUniformLocation(program, "dimensions"),
							.eye_world = glGetUniformLocation(program, "eye_world"),
							.eye_unprojection = glGetUniformLocation(program, "eye_unprojection"),
							.normal_map = glGetUniformLocation(program, "normal_map"),
							.depth_map = glGetUniformLocation(program, "depth_map"),
							.light_positions = glGetUniformLocation(program, "light_positions"),
							.light_colors = glGetUniformLocation(program, "light_colors"),
							.light_directions = glGetUniformLocation(program, "light_directions"),
							.vertex_position = glGetAttribLocation(program, "position"),
							.vertex_texcoord = glGetAttribLocation(program, "texcoord"),
					},
	};

	return material;
}
