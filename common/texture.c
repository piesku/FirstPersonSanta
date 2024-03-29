#include "texture.h"

#include <stdlib.h>

GLuint create_texture_from(uint8_t* pixels, uint32_t width, uint32_t height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return texture;
}

GLuint resize_texture_rgba(GLuint texture, uint32_t width, uint32_t height)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

GLuint create_texture_rgba(uint32_t width, uint32_t height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	return resize_texture_rgba(texture, width, height);
}

GLuint resize_texture_depth(GLuint texture, uint32_t width, uint32_t height)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24,
			width, height, 0, GL_DEPTH_COMPONENT,
			GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

GLuint create_texture_depth(uint32_t width, uint32_t height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	return resize_texture_depth(texture, width, height);
}
