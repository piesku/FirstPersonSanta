#pragma once
#include <stdbool.h>

#include "../common/entity.h"

typedef struct control_player {
	bool move;
	float yaw;
	float pitch;
} ControlPlayer;

struct world;
ControlPlayer* mix_control_player(struct world* world, entity entity);
