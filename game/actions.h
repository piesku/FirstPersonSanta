#pragma once

#include "../common/entity.h"

enum action {
	ACTION_TRIGGER_BOUNCE,
	ACTION_TRIGGER_EXIT,
	ACTION_TRIGGER_PORTAL,
	ACTION_TRIGGER_CHOINKA,
};

union action_data {
	struct action_trigger_data {
		Entity collider;
		Entity other;
	} trigger;
};

struct client;
struct world;

void dispatch(struct client* client, struct world* world, enum action action, union action_data payload);
