#pragma once
#include <math.h>
#include <stdbool.h>

#define EPSILON 0.000001
#define DEG_TO_RAD (M_PI / 180.0)
#define RAD_TO_DEG (180.0 / M_PI)

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef float quat[4];
typedef float mat4[16];

float sign(float x);
float absf(float x);
float minf(float a, float b);
float maxf(float a, float b);
float lerp(float from, float to, float progress);
float clamp(float mini, float maxi, float num);

float vec3_length(vec3 a);
void vec3_normalize(vec3 out, vec3 a);
void vec3_add(vec3 out, vec3 a, vec3 b);
void vec3_subtract(vec3 out, vec3 a, vec3 b);
void vec3_scale(vec3 out, vec3 a, float b);
void vec3_transform_point(vec3 out, vec3 a, mat4 m);
void vec3_transform_direction(vec3 out, vec3 a, mat4 m);

void quat_multiply(quat out, quat a, quat bQuat);
void quat_from_euler(quat out, float x, float y, float z);
void quat_from_axis(quat out, vec3 axis, float angle);

void mat4_identity(mat4 mat);
void mat4_set(mat4 out,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
bool mat4_invert(mat4 out, mat4 mat);
void mat4_multiply(mat4 out, mat4 a, mat4 b);
void mat4_translate(mat4 out, mat4 mat, vec3 vec);
bool mat4_rotate(mat4 out, mat4 mat, float angle, vec3 axis);
void mat4_perspective(mat4 out, float fovy, float aspect, float near, float far);
void mat4_compose(mat4 out, vec3 v, quat q, vec3 s);
void mat4_get_translation(vec3 out, mat4 mat);
