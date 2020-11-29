#include "matrix.h"

#include <math.h>

float vec3_length(const vec3 a)
{
	float x = a[0];
	float y = a[1];
	float z = a[2];
	float len = x * x + y * y + z * z;

	if (len > 0.0f) {
		len = 1.0f / sqrt(len);
	}

	return len;
}

float vec3_dot(const vec3 a, const vec3 b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void vec3_set(vec3 out, float x, float y, float z)
{
	out[0] = x;
	out[1] = y;
	out[2] = z;
}

void vec3_copy(vec3 out, const vec3 a)
{
	out[0] = a[0];
	out[1] = a[1];
	out[2] = a[2];
}

void vec3_normalize(vec3 out, const vec3 a)
{
	float x = a[0];
	float y = a[1];
	float z = a[2];
	float len = x * x + y * y + z * z;

	if (len > 0.0f) {
		len = 1.0f / sqrtf(len);
	}

	out[0] = a[0] * len;
	out[1] = a[1] * len;
	out[2] = a[2] * len;
}

void vec3_add(vec3 out, const vec3 a, const vec3 b)
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

void vec3_subtract(vec3 out, const vec3 a, const vec3 b)
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

void vec3_scale(vec3 out, const vec3 a, float b)
{
	out[0] = a[0] * b;
	out[1] = a[1] * b;
	out[2] = a[2] * b;
}

void vec3_transform_point(vec3 out, const vec3 a, const mat4 m)
{
	float x = a[0], y = a[1], z = a[2];
	float w = m[3] * x + m[7] * y + m[11] * z + m[15];
	w = w || 1.0f;
	out[0] = (m[0] * x + m[4] * y + m[8] * z + m[12]) / w;
	out[1] = (m[1] * x + m[5] * y + m[9] * z + m[13]) / w;
	out[2] = (m[2] * x + m[6] * y + m[10] * z + m[14]) / w;
}

void vec3_transform_direction(vec3 out, const vec3 a, const mat4 m)
{
	vec3 tip;
	vec3 base;
	vec3_transform_point(tip, a, m);
	mat4_get_translation(base, m);
	vec3_subtract(out, tip, base);
}