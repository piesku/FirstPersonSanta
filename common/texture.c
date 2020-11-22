#include "texture.h"

#include "../LodePNG/lodepng.h"

GLuint decode_texture_rgba(uint8_t* png, size_t length)
{
	uint8_t* image = NULL;
	uint32_t width;
	uint32_t height;
	uint32_t error = lodepng_decode32(&image, &width, &height, png, length);
	if (error) {
		return 0;
	}

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return id;
}
