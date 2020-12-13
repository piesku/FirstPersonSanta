#include <stdint.h>
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

Entity load_scene_from_gltf(struct world* world, const char* file_location, vec4* scene_color, bool has_fireplace);

Entity blueprint_camera_follow(struct world* world);
Entity blueprint_player_target(struct world* world, Entity* target);
Entity blueprint_ground(struct world* world);
Entity blueprint_portal(struct world* world);

void sys_transform(struct world* world);

void scene_room_from_file(struct world* world)
{
	srand((uint32_t)time(0));
	const char* available_rooms[] = {
			"scenes/room01.gltf",
			"scenes/room02.gltf",
			"scenes/room03.gltf",
			"scenes/room04.gltf",
			"scenes/room05.gltf",
			"scenes/room06.gltf",
			"scenes/room07.gltf",
			"scenes/room08.gltf",
			"scenes/room09.gltf",
			"scenes/room10.gltf",
	};

	const vec4 base_colors[4] = {
			{0.9f, 0.3f, 0.4f, 1.0f},
			{0.92f, 0.62f, 0.48f, 1.0f},
			{0.94f, 0.51f, 0.0f, 1.0f},
			{0.96f, 0.63f, 0.68f, 1.0f},
	};

	vec4 scene_color = base_colors[rand() % 4];

	{
		// Player.
		Entity target;
		Entity player = blueprint_player_target(world, &target);
		Transform* player_transform = world->transform[player];
		player_transform->translation = (vec3){3, 1, 3};

		Entity camera = blueprint_camera_follow(world);
		Transform* camera_transform = world->transform[camera];
		camera_transform->translation = (vec3){3, 1.5f, 500};
		quat_from_euler(&camera_transform->rotation, 0, 180, 0);

		Mimic* camera_mimic = world->mimic[camera];
		camera_mimic->target = target;
		camera_mimic->stiffness = 0.1f;
	}

	{
		Entity ground = blueprint_ground(world);
		world->render[ground]->colored_unlit.color = scene_color;
	}

	int fireplace_location = rand() % 4;

	Entity first = load_scene_from_gltf(
			world,
			available_rooms[(rand() % 10)],
			&scene_color,
			fireplace_location == 0);
	(void)first;

	Entity second = load_scene_from_gltf(
			world,
			available_rooms[(rand() % 10)],
			&scene_color,
			fireplace_location == 1);
	quat_from_euler(&world->transform[second]->rotation, 0, 90, 0);

	Entity third = load_scene_from_gltf(
			world,
			available_rooms[(rand() % 10)],
			&scene_color,
			fireplace_location == 2);
	quat_from_euler(&world->transform[third]->rotation, 0, 180, 0);

	Entity fourth = load_scene_from_gltf(
			world,
			available_rooms[(rand() % 10)],
			&scene_color,
			fireplace_location == 3);
	quat_from_euler(&world->transform[fourth]->rotation, 0, 270, 0);

	// Commit all transforms before the first frame runs.
	sys_transform(world);
}
