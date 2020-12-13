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

Entity blueprint_camera_follow(struct world* world);
Entity blueprint_player_target(struct world* world, Entity* target);
Entity blueprint_ground(struct world* world);
Entity blueprint_gift(struct world* world);
Entity blueprint_lamp_floor(struct world* world);

void scene_room(struct world* world)
{
	{
		// Player.
		Entity target;
		Entity player = blueprint_player_target(world, &target);
		Transform* player_transform = world->transform[player];
		player_transform->translation = (vec3){0, 1, 5};

		Entity camera = blueprint_camera_follow(world);
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

	{
		// Chair.
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.5f, 0.0f, 0.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CHAIR;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	{
		// Lamp.
		Entity lamp = blueprint_lamp_floor(world);

		Transform* lamp_transform = mix_transform(world, lamp);
		lamp_transform->translation = (vec3){-0.5f, 0.0f, 0.2f};
		quat_from_euler(&lamp_transform->rotation, 0.0f, -130.0f, 0.0f);
	}

	{
		// Gift.
		Entity entity = blueprint_gift(world);

		Transform* transform = world->transform[entity];
		transform->translation = (vec3){0.5f, 0.25f, 1.5f};
		quat_from_euler(&transform->rotation, 0.0f, -65.0f, 0.0f);
	}

	{
		// Building 1.
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){-5.0f, 0.0f, -8.0f};
		transform->scale = (vec3){10.0f, 20.0f, 10.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	{
		// Building 2.
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){10.0f, 0.0f, -15.0f};
		transform->scale = (vec3){50.0f, 40.0f, 10.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}
}
