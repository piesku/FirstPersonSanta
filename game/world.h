#pragma once

#include "../common/entity.h"

#define MAX_ENTITIES 10001

enum has_component {
	HAS_CAMERA = 1 << 0,
	HAS_COLLIDE = 1 << 1,
	HAS_CONTROL_PLAYER = 1 << 2,
	HAS_MOVE = 1 << 3,
	HAS_LIGHT = 1 << 4,
	HAS_RENDER = 1 << 5,
	HAS_RIGID_BODY = 1 << 6,
	HAS_TRANSFORM = 1 << 7,
};

struct world {
	signature signature[MAX_ENTITIES];

	union camera* camera[MAX_ENTITIES];
	struct collide* collide[MAX_ENTITIES];
	struct control_player* control_player[MAX_ENTITIES];
	struct move* move[MAX_ENTITIES];
	union light* light[MAX_ENTITIES];
	union render* render[MAX_ENTITIES];
	struct rigid_body* rigid_body[MAX_ENTITIES];
	struct transform* transform[MAX_ENTITIES];
};

struct world* create_world(void);
entity create_entity(struct world* world);
void destroy_entity(struct world* world, entity entity);
