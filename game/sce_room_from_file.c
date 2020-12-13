#include <stdio.h>
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

Entity load_scene_from_gltf(struct world* world, const char* file_location, bool has_fireplace);

Entity blueprint_camera_follow(struct world* world);
Entity blueprint_player_target(struct world* world, Entity* target);
Entity blueprint_ground(struct world* world);
Entity blueprint_portal(struct world* world);

void sys_transform(struct world* world);

void scene_room_from_file(struct world* world)
{
	srand(time(0));

	{
		// Player.
		Entity target;
		Entity player = blueprint_player_target(world, &target);
		Transform* player_transform = world->transform[player];
		player_transform->translation = (vec3){3, 1, 5};

		Entity camera = blueprint_camera_follow(world);
		Transform* camera_transform = world->transform[camera];
		camera_transform->translation = (vec3){3, 1.5f, 500};
		quat_from_euler(&camera_transform->rotation, 0, 180, 0);

		Mimic* camera_mimic = world->mimic[camera];
		camera_mimic->target = target;
		camera_mimic->stiffness = 0.1f;
	}

	{
		blueprint_ground(world);
	}

	int fireplace_location = rand() % 4;

	Entity first = load_scene_from_gltf(world, "scenes/room02.gltf", fireplace_location == 0);
	(void)first;

	Entity second = load_scene_from_gltf(world, "scenes/room06.gltf", fireplace_location == 1);
	quat_from_euler(&world->transform[second]->rotation, 0, 90, 0);

	Entity third = load_scene_from_gltf(world, "scenes/room03.gltf", fireplace_location == 2);
	quat_from_euler(&world->transform[third]->rotation, 0, 180, 0);

	Entity fourth = load_scene_from_gltf(world, "scenes/room05.gltf", fireplace_location == 3);
	quat_from_euler(&world->transform[fourth]->rotation, 0, 270, 0);

	// Commit all transforms before the first frame runs.
	sys_transform(world);
}
