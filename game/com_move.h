#pragma once
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"

enum move_dirty {
	MOVE_DIRTY_NONE = 0,
	MOVE_DIRTY_DIRECTION = 1,
	MOVE_DIRTY_LOCAL_ROTATION = 2,
	MOVE_DIRTY_SELF_ROTATION = 4,
};

typedef struct move {
	float movement_speed;
	float rotation_speed;
	vec3 direction;
	quat local_rotation;
	quat self_rotation;
	int8_t dirty;
} Move;

struct world;
Move* mix_move(struct world* world, entity entity);
