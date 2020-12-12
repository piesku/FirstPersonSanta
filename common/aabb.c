#include "aabb.h"

const vec3 bounding_box[] = {
		{0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, 0.5f},
};

void compute_aabb_with_scale(mat4* world, struct aabb* aabb)
{
	mat4_get_translation(&aabb->center, world);

	// Start with the extents on each axis set to the position of the center.
	float min_x, min_y, min_z, max_x, max_y, max_z;
	min_x = max_x = aabb->center.x;
	min_y = max_y = aabb->center.y;
	min_z = max_z = aabb->center.z;

	// Expand the extents outwards from the center by finding the farthest
	// vertex on each axis in both the negative and the positive direction.
	for (int i = 0; i < 8; i++) {
		vec3 bb_vertex = bounding_box[i];

		// Scale the bounding box according to the size of the collider.
		vec3 world_vertex = {
				bb_vertex.x * aabb->size.x,
				bb_vertex.y * aabb->size.y,
				bb_vertex.z * aabb->size.z,
		};

		vec3_transform_point(&world_vertex, &world_vertex, world);
		if (world_vertex.x < min_x) {
			min_x = world_vertex.x;
		}
		if (world_vertex.x > max_x) {
			max_x = world_vertex.x;
		}
		if (world_vertex.y < min_y) {
			min_y = world_vertex.y;
		}
		if (world_vertex.y > max_y) {
			max_y = world_vertex.y;
		}
		if (world_vertex.z < min_z) {
			min_z = world_vertex.z;
		}
		if (world_vertex.z > max_z) {
			max_z = world_vertex.z;
		}
	}

	// Save the min and max bounds.
	aabb->min = (vec3){min_x, min_y, min_z};
	aabb->max = (vec3){max_x, max_y, max_z};

	// Calculate the half-extents.
	aabb->half = (vec3){
			(max_x - min_x) / 2,
			(max_y - min_y) / 2,
			(max_z - min_z) / 2,
	};
}

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
