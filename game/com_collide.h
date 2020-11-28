#pragma once

#include <stdint.h>

#include "../common/aabb.h"
#include "../common/entity.h"
#include "../common/matrix.h"

#define MAX_COLLISIONS 5

enum layer_mask {
	LAYER_NONE = 1 << 0,
	LAYER_PLAYER = 1 << 1,
	LAYER_TERRAIN = 1 << 2,
};

struct collision {
	entity other;
	vec3 hit;
};

typedef struct collide {
	entity entity;
	bool dynamic;
	enum layer_mask layers;
	enum layer_mask mask;
	struct aabb aabb;
	int8_t count;
	struct collision collisions[MAX_COLLISIONS];
} Collide;

struct world;
Collide* mix_collide(struct world* world, entity entity);
