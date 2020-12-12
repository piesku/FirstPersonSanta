#pragma once

#include <stdbool.h>

#include "matrix.h"

struct aabb {
	// The size of the AABB in self units.
	vec3 size;
	// The min corner of the AABB.
	vec3 min;
	// The max corner of the AABB.
	vec3 max;
	// The world position of the AABB.
	vec3 center;
	// The half-extents of the AABB on the three axes.
	vec3 half;
};

void compute_aabb_with_scale(mat4* world, struct aabb* aabb);
void compute_aabb_without_scale(mat4* world, struct aabb* aabb);
void penetrate_aabb(vec3* out, struct aabb* a, struct aabb* b);
bool intersect_aabb(struct aabb* a, struct aabb* b);
