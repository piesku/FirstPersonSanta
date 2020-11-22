#include "materials.h"
#include "program.h"

struct material mat_diffuse_gouraud(void)
{
	GLchar vertex_shader_source[] =
			"#version 300 es\n"

			"/* See client.light_positions */"
			"const int MAX_LIGHTS = 8;"

			"uniform mat4 pv;"
			"uniform mat4 world;"
			"uniform mat4 self;"
			"uniform vec4 color;"
			"uniform vec4 light_positions[MAX_LIGHTS];"
			"uniform vec4 light_details[MAX_LIGHTS];"

			"in vec3 position;"
			"in vec3 normal;"

			"out vec4 vert_color;"

			"void main() {"
			"	vec4 vert_pos = world * vec4(position, 1.0);"
			"	vec3 vert_normal = normalize((vec4(normal, 1.0) * self).xyz);"
			"	gl_Position = pv * vert_pos;"

			"	/* Ambient light */"
			"	vec3 rgb = color.rgb * 0.1;"

			"	for (int i = 0; i < MAX_LIGHTS; i++) {"
			"		if (light_positions[i].w == 0.0) {"
			"			break;"
			"		}"

			"		vec3 light_color = light_details[i].rgb;"
			"		float light_intensity = light_details[i].a;"

			"		vec3 light_normal;"
			"		if (light_positions[i].w == 1.0) {"
			"			/* Directional light */"
			"			light_normal = light_positions[i].xyz;"
			"		} else {"
			"			vec3 light_dir = light_positions[i].xyz - vert_pos.xyz;"
			"			float light_dist = length(light_dir);"
			"			light_normal = light_dir / light_dist;"
			"			/* Distance attenuation */"
			"			light_intensity /= (light_dist * light_dist);"
			"		}"

			"		float diffuse_factor = dot(vert_normal, light_normal);"
			"		if (diffuse_factor > 0.0) {"
			"			/* Diffuse color */"
			"			rgb += color.rgb * diffuse_factor * light_color * light_intensity;"
			"		}"
			"	}"

			"	vert_color = vec4(rgb, 1.0);"
			"}";
	GLchar fragment_shader_source[] =
			"#version 300 es\n"
			"precision mediump float;"
			"in vec4 vert_color;"
			"out vec4 frag_color;"
			"void main() {"
			"	frag_color = vert_color;"
			"}";
	GLuint program = create_program(vertex_shader_source, fragment_shader_source);
	struct material material = (struct material) {
		.mode = GL_TRIANGLES,
		.program = program,
		.layout.diffuse = (struct layout_diffuse){
			.pv = glGetUniformLocation(program, "pv"),
			.world = glGetUniformLocation(program, "world"),
			.self = glGetUniformLocation(program, "self"),
			.color = glGetUniformLocation(program, "color"),
			.light_positions = glGetUniformLocation(program, "light_positions"),
			.light_details = glGetUniformLocation(program, "light_details"),
			.vertex_position = glGetAttribLocation(program, "position"),
			.vertex_normal = glGetAttribLocation(program, "normal"),
		},
	};
	return material;
}
