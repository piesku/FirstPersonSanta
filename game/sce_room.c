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

entity blueprint_camera_follow(struct world* world);
entity blueprint_player_target(struct world* world, entity* target);
entity blueprint_ground(struct world* world);
entity blueprint_gift(struct world* world);
entity blueprint_sofa(struct world* world);
entity blueprint_lamp(struct world* world);

void scene_room(struct world* world)
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

	{
		// Chair.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.5f, 0.0f, 0.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CHAIR;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	{
		// Sofa.
		entity sofa = blueprint_sofa(world);

		Transform* transform = world->transform[sofa];
		transform->translation = (vec3){2.0f, 0.0f, 2.0f};
		quat_from_euler(&transform->rotation, 0.0f, -60.0f, 0.0f);
	}

	{
		// Lamp.
		entity lamp = blueprint_lamp(world);

		Transform* lamp_transform = mix_transform(world, lamp);
		lamp_transform->translation = (vec3){-0.5f, 0.0f, 0.2f};
		quat_from_euler(&lamp_transform->rotation, 0.0f, -130.0f, 0.0f);
	}

	{
		// Gift.
		entity entity = blueprint_gift(world);

		Transform* transform = world->transform[entity];
		transform->translation = (vec3){0.5f, 0.25f, 1.5f};
		quat_from_euler(&transform->rotation, 0.0f, -65.0f, 0.0f);
	}

	{
		// Building 1.
		entity entity = create_entity(world);

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
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){10.0f, 0.0f, -15.0f};
		transform->scale = (vec3){50.0f, 40.0f, 10.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}
}
