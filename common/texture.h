#pragma once

#include <inttypes.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

GLuint create_texture_rgba(uint8_t* pixels, uint32_t width, uint32_t height);
