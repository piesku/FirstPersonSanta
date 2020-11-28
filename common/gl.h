#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_NO_GLU
#include <GL/glew.h>
#endif
