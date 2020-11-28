#pragma once

#include <stdint.h>

#include "gl.h"

GLuint create_texture_rgba(uint8_t* pixels, uint32_t width, uint32_t height);
