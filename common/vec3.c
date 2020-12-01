#include "matrix.h"

#include <math.h>

float vec3_length(const vec3 a)
{
	float x = a.x;
	float y = a.y;
	float z = a.z;
	float len = x * x + y * y + z * z;

	if (len > 0.0f) {
		len = 1.0f / sqrt(len);
	}

	return len;
}

float vec3_dot(const vec3 a, const vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

void vec3_set(vec3* out, float x, float y, float z)
{
	out->x = x;
	out->y = y;
	out->z = z;
}

void vec3_copy(vec3* out, const vec3 a)
{
	out->x = a.x;
	out->y = a.y;
	out->z = a.z;
}

void vec3_normalize(vec3* out, const vec3 a)
{
	float x = a.x;
	float y = a.y;
	float z = a.z;
	float len = x * x + y * y + z * z;

	if (len > 0.0f) {
		len = 1.0f / sqrtf(len);
	}

	out->x = a.x * len;
	out->y = a.y * len;
	out->z = a.z * len;
}

void vec3_add(vec3* out, const vec3 a, const vec3 b)
{
	out->x = a.x + b.x;
	out->y = a.y + b.y;
	out->z = a.z + b.z;
}

void vec3_subtract(vec3* out, const vec3 a, const vec3 b)
{
	out->x = a.x - b.x;
	out->y = a.y - b.y;
	out->z = a.z - b.z;
}

void vec3_scale(vec3* out, const vec3 a, float b)
{
	out->x = a.x * b;
	out->y = a.y * b;
	out->z = a.z * b;
}

void vec3_transform_point(vec3* out, const vec3 a, const mat4 m)
{
	float x = a.x, y = a.y, z = a.z;
	float w = m[3] * x + m[7] * y + m[11] * z + m[15];
	w = w || 1.0f;
	out->x = (m[0] * x + m[4] * y + m[8] * z + m[12]) / w;
	out->y = (m[1] * x + m[5] * y + m[9] * z + m[13]) / w;
	out->z = (m[2] * x + m[6] * y + m[10] * z + m[14]) / w;
}

void vec3_transform_direction(vec3* out, const vec3 a, const mat4 m)
{
	vec3 tip;
	vec3 base;
	vec3_transform_point(&tip, a, m);
	mat4_get_translation(&base, m);
	vec3_subtract(out, tip, base);
}
