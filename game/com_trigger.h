#pragma once

#include "../common/aabb.h"
#include "../common/entity.h"
#include "../common/matrix.h"
#include "actions.h"
#include "com_collide.h"

typedef struct trigger {
	enum action action;
	layer_mask mask;
} Trigger;

struct world;
Trigger* mix_trigger(struct world* world, Entity entity);
