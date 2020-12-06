#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#define glCreateFramebuffers glGenFramebuffers
#include <OpenGL/gl3.h>
#else
#define GLEW_NO_GLU
#include <GL/glew.h>
#endif
