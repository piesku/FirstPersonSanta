#include "matrix.h"

void vec4_lerp(vec4* out, const vec4* a, const vec4* b, float t)
{
	out->x = a->x + t * (b->x - a->x);
	out->y = a->y + t * (b->y - a->y);
	out->z = a->z + t * (b->z - a->z);
	out->w = a->w + t * (b->w - a->w);
}
