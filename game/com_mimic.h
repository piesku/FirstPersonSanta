#pragma once

#include "../common/entity.h"

typedef struct mimic {
	Entity target;
	float stiffness;
} Mimic;

struct world;
Mimic* mix_mimic(struct world* world, Entity entity);
