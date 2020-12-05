#pragma once

#include "../common/aabb.h"
#include "../common/entity.h"
#include "../common/matrix.h"

typedef struct trigger {
	enum action action;
} Trigger;

struct world;
Trigger* mix_trigger(struct world* world, entity entity);
