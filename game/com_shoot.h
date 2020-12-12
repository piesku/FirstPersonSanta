#pragma once

#include <stdbool.h>

#include "../common/entity.h"

typedef struct shoot {
	bool trigger;
	float frequency;
	float since_last;
} Shoot;

struct world;
Shoot* mix_shoot(struct world* world, Entity entity);
