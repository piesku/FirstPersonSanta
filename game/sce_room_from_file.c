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

Entity load_scene_from_gltf(struct world* world, const char* file_location);

Entity blueprint_camera_follow(struct world* world);
Entity blueprint_player_target(struct world* world, Entity* target);
Entity blueprint_ground(struct world* world);

void scene_room_from_file(struct world* world)
{
	{
		// Player.
		Entity target;
		Entity player = blueprint_player_target(world, &target);
		Transform* player_transform = world->transform[player];
		player_transform->translation = (vec3){3, 1, 5};

		Entity camera = blueprint_camera_follow(world);
		Transform* camera_transform = world->transform[camera];
		camera_transform->translation = (vec3){3, 50, 1000};
		quat_from_euler(&camera_transform->rotation, 30, 180, 0);

		Mimic* camera_mimic = world->mimic[camera];
		camera_mimic->target = target;
		camera_mimic->stiffness = 0.1f;
	}

	{
		blueprint_ground(world);
	}

	Entity first = load_scene_from_gltf(world, "scenes/room01.gltf");
	(void)first;

	Entity second = load_scene_from_gltf(world, "scenes/room02.gltf");
	quat_from_euler(&world->transform[second]->rotation, 0, 90, 0);

	Entity third = load_scene_from_gltf(world, "scenes/room03.gltf");
	quat_from_euler(&world->transform[third]->rotation, 0, 180, 0);

	Entity fourth = load_scene_from_gltf(world, "scenes/room04.gltf");
	quat_from_euler(&world->transform[fourth]->rotation, 0, 270, 0);
}
