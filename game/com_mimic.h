#pragma once

#include "../common/entity.h"

typedef struct mimic {
	Entity target;
	float movement_stiffness;
	float rotation_stiffness;
} Mimic;

struct world;
Mimic* mix_mimic(struct world* world, Entity entity);
