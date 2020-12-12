#pragma once

#include "../common/entity.h"

#define MAX_ENTITIES 10001

enum component_index {
	INDEX_CAMERA,
	INDEX_COLLIDE,
	INDEX_CONTROL_PLAYER,
	INDEX_MIMIC,
	INDEX_MOVE,
	INDEX_LIGHT,
	INDEX_RENDER,
	INDEX_RIGID_BODY,
	INDEX_SHOOT,
	INDEX_TRANSFORM,
	INDEX_TRIGGER,
};

enum has_component {
	HAS_CAMERA = 1 << INDEX_CAMERA,
	HAS_COLLIDE = 1 << INDEX_COLLIDE,
	HAS_CONTROL_PLAYER = 1 << INDEX_CONTROL_PLAYER,
	HAS_MIMIC = 1 << INDEX_MIMIC,
	HAS_MOVE = 1 << INDEX_MOVE,
	HAS_LIGHT = 1 << INDEX_LIGHT,
	HAS_RENDER = 1 << INDEX_RENDER,
	HAS_RIGID_BODY = 1 << INDEX_RIGID_BODY,
	HAS_SHOOT = 1 << INDEX_SHOOT,
	HAS_TRANSFORM = 1 << INDEX_TRANSFORM,
	HAS_TRIGGER = 1 << INDEX_TRIGGER,
};

struct world {
	Signature signature[MAX_ENTITIES];

	union camera* camera[MAX_ENTITIES];
	struct collide* collide[MAX_ENTITIES];
	struct control_player* control_player[MAX_ENTITIES];
	struct mimic* mimic[MAX_ENTITIES];
	struct move* move[MAX_ENTITIES];
	union light* light[MAX_ENTITIES];
	union render* render[MAX_ENTITIES];
	struct rigid_body* rigid_body[MAX_ENTITIES];
	struct shoot* shoot[MAX_ENTITIES];
	struct transform* transform[MAX_ENTITIES];
	struct trigger* trigger[MAX_ENTITIES];
};

struct world* create_world(void);
void destroy_world(struct world* world);
Entity create_entity(struct world* world);
void destroy_entity(struct world* world, Entity entity);
