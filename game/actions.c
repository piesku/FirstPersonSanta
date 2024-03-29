#include "actions.h"

#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

void scene_bounce(struct world* world);
void scene_monkey(struct world* world);
void scene_room(struct world* world);
void scene_room_from_file(struct world* world);

void dispatch(struct client* client, struct world* world, enum action action, union action_data payload)
{
	switch (action) {
		case ACTION_TRIGGER_BOUNCE: {
			RigidBody* rigid_body = world->rigid_body[payload.trigger.other];
			rigid_body->acceleration.y += 1000.0f;
			break;
		}
		case ACTION_TRIGGER_PORTAL: {
			Entity portal = payload.trigger.collider;
			Entity player = payload.trigger.other;

			Entity fireplace = world->transform[portal]->parent;
			Entity exit = world->transform[fireplace]->children.entities[1];

			Transform* exit_transform = world->transform[exit];
			Transform* player_transform = world->transform[player];
			mat4_get_translation(&player_transform->translation, &exit_transform->world);
			mat4_get_rotation(&player_transform->rotation, &exit_transform->world);

			break;
		}
		case ACTION_TRIGGER_EXIT: {
			client->next_scene = &scene_room_from_file;
			break;
		}

		case ACTION_TRIGGER_CHOINKA: {
			Entity gift = payload.trigger.other;
			Transform* gift_transform = world->transform[gift];
			for (size_t i = 0; i < gift_transform->children.size; i++) {
				destroy_entity(world, gift_transform->children.entities[i]);
			}
			destroy_entity(world, gift);

			Entity choinka_collider = payload.trigger.collider;
			Entity choinka = world->transform[choinka_collider]->parent;
			Transform* choinka_transform = world->transform[choinka];
			RenderColoredUnlit* choinka_render = &world->render[choinka]->colored_unlit;
			Entity choinka_target = choinka_transform->children.entities[1];

			if (world->transform[choinka_target]->translation.y > 0.0f) {
				world->transform[choinka_target]->translation.y = 0.0f;
				world->signature[choinka_collider] &= HAS_COLLIDE;
				choinka_render->color = (vec4){0.25f, 0.45f, 0.2f, 1.0f};
			} else {
				world->transform[choinka_target]->translation.y += 0.2f;
			}
			break;
		}

		default:
			printf("Unknown action: %d", action);
			exit(1);
	}
}
