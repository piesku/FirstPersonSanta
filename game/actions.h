#pragma once

#include "../common/entity.h"

enum action {
	ACTION_TRIGGER_BOUNCE,
};

union action_data {
	struct action_trigger_data {
		entity collider;
		entity other;
	} trigger;
};

void dispatch(struct client* client, struct world* world, enum action action, union action_data payload);
