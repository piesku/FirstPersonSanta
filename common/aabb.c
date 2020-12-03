#include "aabb.h"

void compute_aabb_without_scale(mat4* world, struct aabb* aabb)
{
	mat4_get_translation(&aabb->center, world);
	vec3_scale(&aabb->half, &aabb->size, 0.5f);
	vec3_subtract(&aabb->min, &aabb->center, &aabb->half);
	vec3_add(&aabb->max, &aabb->center, &aabb->half);
}

void penetrate_aabb(vec3* out, struct aabb* a, struct aabb* b)
{
	float distance_x = a->center.x - b->center.x;
	float penetration_x = a->half.x + b->half.x - absf(distance_x);

	float distance_y = a->center.y - b->center.y;
	float penetration_y = a->half.y + b->half.y - absf(distance_y);

	float distance_z = a->center.z - b->center.z;
	float penetration_z = a->half.z + b->half.z - absf(distance_z);

	if (penetration_x < penetration_y && penetration_x < penetration_z) {
		out->x = penetration_x * signf(distance_x);
		out->y = 0;
		out->z = 0;
	} else if (penetration_y < penetration_z) {
		out->x = 0;
		out->y = penetration_y * signf(distance_y);
		out->z = 0;
	} else {
		out->x = 0;
		out->y = 0;
		out->z = penetration_z * signf(distance_z);
	}
}

bool intersect_aabb(struct aabb* a, struct aabb* b)
{
	return a->min.x < b->max.x
		&& a->max.x > b->min.x
		&& a->min.y < b->max.y
		&& a->max.y > b->min.y
		&& a->min.z < b->max.z
		&& a->max.z > b->min.z;
}
