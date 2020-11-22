#include <stdio.h>
#include <stdlib.h>

#include "material.h"

GLuint create_program(const GLchar* vertex_shader_source, const GLchar* fragment_shader_source)
{
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader_source, NULL);
	glCompileShader(vs);

	GLint vertex_status;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &vertex_status);
	if (vertex_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(vs, 1024, &log_length, message);
		printf("Shader compilation error: %s", message);
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader_source, NULL);
	glCompileShader(fs);

	GLint fragment_status;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &fragment_status);
	if (fragment_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(fs, 1024, &log_length, message);
		printf("Shader compilation error: %s", message);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glDeleteShader(vs);
	glAttachShader(program, fs);
	glDeleteShader(fs);
	glLinkProgram(program);

	GLint link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		printf("Shader link error: %s", message);
	}

	return program;
}
