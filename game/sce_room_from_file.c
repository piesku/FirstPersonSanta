#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_collide.h"
#include "com_light.h"
#include "com_mimic.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "com_trigger.h"
#include "index.h"
#include "world.h"

void load_scene_from_gltf(struct world* world, const char* file_location);

entity blueprint_camera_follow(struct world* world);
entity blueprint_player_target(struct world* world, entity* target);
entity blueprint_ground(struct world* world);

void scene_room_from_file(struct world* world)
{

	{
		// Player.
		entity target;
		entity player = blueprint_player_target(world, &target);
		Transform* player_transform = world->transform[player];
		player_transform->translation = (vec3){0.0f, 1.7f, 5.0f};

		entity camera = blueprint_camera_follow(world);
		Transform* camera_transform = world->transform[camera];
		camera_transform->translation = (vec3){0.0f, 50.0f, 1000.0f};
		quat_from_euler(&camera_transform->rotation, 30.0f, 180.0f, 0.0f);

		Mimic* camera_mimic = world->mimic[camera];
		camera_mimic->target = target;
		camera_mimic->stiffness = 0.1f;
	}

	{
		blueprint_ground(world);
	}

	load_scene_from_gltf(world, "scenes/scene2.gltf");
}
