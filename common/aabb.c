#include "aabb.h"

void compute_aabb_without_scale(mat4 world, struct aabb* aabb)
{
	mat4_get_translation(aabb->center, world);
	vec3_scale(aabb->half, aabb->size, 0.5f);
	vec3_subtract(aabb->min, aabb->center, aabb->half);
	vec3_add(aabb->max, aabb->center, aabb->half);
}

void penetrate_aabb(vec3 out, struct aabb* a, struct aabb* b)
{
	float distance_x = a->center[0] - b->center[0];
	float penetration_x = a->half[0] + b->half[0] - absf(distance_x);

	float distance_y = a->center[1] - b->center[1];
	float penetration_y = a->half[1] + b->half[1] - absf(distance_y);

	float distance_z = a->center[2] - b->center[2];
	float penetration_z = a->half[2] + b->half[2] - absf(distance_z);

	if (penetration_x < penetration_y && penetration_x < penetration_z) {
		out[0] = penetration_x * signf(distance_x);
		out[1] = 0;
		out[2] = 0;
	} else if (penetration_y < penetration_z) {
		out[0] = 0;
		out[1] = penetration_y * signf(distance_y);
		out[2] = 0;
	} else {
		out[0] = 0;
		out[1] = 0;
		out[2] = penetration_z * signf(distance_z);
	}
}

bool intersect_aabb(struct aabb* a, struct aabb* b)
{
	return a->min[0] < b->max[0]
		&& a->max[0] > b->min[0]
		&& a->min[1] < b->max[1]
		&& a->max[1] > b->min[1]
		&& a->min[2] < b->max[2]
		&& a->max[2] > b->min[2];
}
