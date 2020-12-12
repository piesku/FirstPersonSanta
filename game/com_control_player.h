#pragma once
#include <stdbool.h>

#include "../common/entity.h"

typedef struct control_player {
	bool move;
	bool shoot;
	float yaw;
	float pitch;
} ControlPlayer;

struct world;
ControlPlayer* mix_control_player(struct world* world, Entity entity);
