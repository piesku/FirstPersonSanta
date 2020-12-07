#pragma once

#include "../common/entity.h"

typedef struct mimic {
	entity target;
	float stiffness;
} Mimic;

struct world;
Mimic* mix_mimic(struct world* world, entity entity);
