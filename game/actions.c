#include "actions.h"

#include <stdio.h>
#include <stdlib.h>

#include "com_rigid_body.h"
#include "client.h"
#include "world.h"

void scene_bounce(struct world* world);
void scene_monkey(struct world* world);
void scene_room(struct world* world);

void dispatch(struct client* client, struct world* world, enum action action, union action_data payload)
{
	switch (action) {
		case ACTION_TRIGGER_BOUNCE: {
			RigidBody* rigid_body = world->rigid_body[payload.trigger.other];
			rigid_body->acceleration.y += 1000.0f;
			break;
		}
		case ACTION_TRIGGER_PLAY: {
			client->next_scene = &scene_bounce;
			break;
		}
		default:
			printf("Unknown action: %d", action);
			exit(1);
	}
}
