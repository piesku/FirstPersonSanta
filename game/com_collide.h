#pragma once

#include <stdint.h>

#include "../common/aabb.h"
#include "../common/entity.h"
#include "../common/matrix.h"

#define MAX_COLLISIONS 2

enum layer_mask {
	LAYER_NONE,
	LAYER_PLAYER,
	LAYER_TERRAIN,
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
