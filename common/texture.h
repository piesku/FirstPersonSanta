#pragma once

#include <stdint.h>

#include "gl.h"

GLuint create_texture_from(uint8_t* pixels, uint32_t width, uint32_t height);
GLuint create_texture_rgba(uint32_t width, uint32_t height);
GLuint create_texture_depth(uint32_t width, uint32_t height);
