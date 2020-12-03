#include "matrix.h"

#include <math.h>

float vec3_length(const vec3* a)
{
	float x = a->x;
	float y = a->y;
	float z = a->z;
	float len = x * x + y * y + z * z;

	if (len > 0.0f) {
		len = 1.0f / sqrt(len);
	}

	return len;
}

float vec3_dot(const vec3* a, const vec3* b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vec3_set(vec3* out, float x, float y, float z)
{
	out->x = x;
	out->y = y;
	out->z = z;
}

void vec3_copy(vec3* out, const vec3* a)
{
	out->x = a->x;
	out->y = a->y;
	out->z = a->z;
}

void vec3_normalize(vec3* out, const vec3* a)
{
	float x = a->x;
	float y = a->y;
	float z = a->z;
	float len = x * x + y * y + z * z;

	if (len > 0.0f) {
		len = 1.0f / sqrtf(len);
	}

	out->x = a->x * len;
	out->y = a->y * len;
	out->z = a->z * len;
}

void vec3_add(vec3* out, const vec3* a, const vec3* b)
{
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
}

void vec3_subtract(vec3* out, const vec3* a, const vec3* b)
{
	out->x = a->x - b->x;
	out->y = a->y - b->y;
	out->z = a->z - b->z;
}

void vec3_scale(vec3* out, const vec3* a, float b)
{
	out->x = a->x * b;
	out->y = a->y * b;
	out->z = a->z * b;
}

void vec3_transform_point(vec3* out, const vec3* a, const mat4* m)
{
	float x = a->x, y = a->y, z = a->z;
	float w = m->m03 * x + m->m13 * y + m->m23 * z + m->m33;
	w = w || 1.0f;
	out->x = (m->m00 * x + m->m10 * y + m->m20 * z + m->m30) / w;
	out->y = (m->m01 * x + m->m11 * y + m->m21 * z + m->m31) / w;
	out->z = (m->m02 * x + m->m12 * y + m->m22 * z + m->m32) / w;
}

void vec3_transform_direction(vec3* out, const vec3* a, const mat4* m)
{
	vec3 tip;
	vec3 base;
	vec3_transform_point(&tip, a, m);
	mat4_get_translation(&base, m);
	vec3_subtract(out, &tip, &base);
}
