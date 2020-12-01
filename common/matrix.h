#pragma once

#include <math.h>
#include <stdbool.h>

#define EPSILON 0.000001f
#define PI 3.14159265358979323846f
#define DEG_TO_RAD (PI / 180.0f)
#define RAD_TO_DEG (180.0f / PI)

typedef struct vec2 {
	float x;
	float y;
} vec2;

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

typedef struct vec4 {
	float x;
	float y;
	float z;
	float w;
} vec4;

typedef struct quat {
	float x;
	float y;
	float z;
	float w;
} quat;

typedef struct mat4 {
	float m00; float m01; float m02; float m03;
	float m10; float m11; float m12; float m13;
	float m20; float m21; float m22; float m23;
	float m30; float m31; float m32; float m33;
} mat4;

float signf(float x);
float absf(float x);
float minf(float a, float b);
float maxf(float a, float b);
float lerp(float from, float to, float progress);
float clamp(float mini, float maxi, float num);

float vec3_length(const vec3 a);
float vec3_dot(const vec3 a, const vec3 b);
void vec3_set(vec3* out, float x, float y, float z);
void vec3_copy(vec3* out, const vec3 a);
void vec3_normalize(vec3* out, const vec3 a);
void vec3_add(vec3* out, const vec3 a, const vec3 b);
void vec3_subtract(vec3* out, const vec3 a, const vec3 b);
void vec3_scale(vec3* out, const vec3 a, float b);
void vec3_transform_point(vec3* out, const vec3 a, const mat4 m);
void vec3_transform_direction(vec3* out, const vec3 a, const mat4 m);

void quat_multiply(quat* out, const quat a, const quat b);
void quat_from_euler(quat* out, float x, float y, float z);
void quat_from_axis(quat* out, const vec3 axis, float angle);
void quat_lerp(quat* out, const quat a, const quat b, float t);
void quat_slerp(quat* out, const quat a, const quat b, float t);

void mat4_identity(mat4* a);
void mat4_set(mat4* out,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
bool mat4_invert(mat4* out, const mat4 a);
void mat4_multiply(mat4* out, const mat4 a, const mat4 b);
void mat4_translate(mat4* out, const mat4 mat, const vec3 vec);
bool mat4_rotate(mat4* out, const mat4 mat, float angle, const vec3 axis);
void mat4_perspective(mat4* out, float fovy, float aspect, float near, float far);
void mat4_compose(mat4* out, const vec3 v, const quat q, const vec3 s);
void mat4_get_translation(vec3* out, const mat4 mat);
