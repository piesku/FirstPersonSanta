#pragma once

#include <stdint.h>

#include "../common/aabb.h"
#include "../common/entity.h"
#include "../common/matrix.h"

#define MAX_COLLISIONS 5

typedef int32_t layer_mask;

enum layer_flag {
	LAYER_NONE = 1 << 0,
	LAYER_PLAYER = 1 << 1,
	LAYER_CAMERA = 1 << 2,
	LAYER_TERRAIN = 1 << 3,
	LAYER_MOVABLE = 1 << 4,
};

struct collision {
	Entity other;
	vec3 hit;
};

typedef struct collide {
	Entity entity;
	bool dynamic;
	layer_mask layers;
	layer_mask mask;
	struct aabb aabb;
	int8_t count;
	struct collision collisions[MAX_COLLISIONS];
} Collide;

struct world;
Collide* mix_collide(struct world* world, Entity entity);
