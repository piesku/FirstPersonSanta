#include "texture.h"

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

	return texture;
}

GLuint create_texture_rgba(uint32_t width, uint32_t height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

GLuint create_texture_depth(uint32_t width, uint32_t height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16,
			width, height, 0, GL_DEPTH_COMPONENT,
			GL_UNSIGNED_INT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}
