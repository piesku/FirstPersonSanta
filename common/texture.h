#pragma once

#include <inttypes.h>
#include <stddef.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

GLuint decode_texture_rgba(uint8_t* png, size_t length);
