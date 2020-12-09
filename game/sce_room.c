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
entity blueprint_camera_player(struct world* world);
entity blueprint_gift(struct world* world);

void scene_room(struct world* world)
{
	// Scale for all furniture.
	float s = 3.0f;

	{
		entity player = blueprint_camera_player(world);
		Transform* transform = world->transform[player];
		transform->translation = (vec3){0.0f, 1.7f, 5.0f};

		entity player_rig = transform->children[0];
		Transform* rig_transform = world->transform[player_rig];
		entity player_camera = rig_transform->children[0];
		world->signature[player_camera] &= ~HAS_CAMERA;

		Collide* collide = mix_collide(world, player);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;

		{
			entity camera = blueprint_camera_follow(world);
			Transform* camera_transform = world->transform[camera];
			camera_transform->translation = (vec3){0.0f, 50.0f, 1000.0f};
			quat_from_euler(&camera_transform->rotation, 30.0f, 180.0f, 0.0f);

			Mimic* mimic = world->mimic[camera];
			mimic->target = player_rig;
			mimic->stiffness = 0.1f;
		}
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation.y = -50.0f;
		transform->scale = (vec3){100.0f, 100.0f, 100.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = false;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_NONE;
		collide->aabb.size = (vec3){100.0f, 100.0f, 100.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_STATIC;
	}

	{
		// Chair.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.0f, 0.0f, 0.0f};
		transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};
		transform->scale = (vec3){s, s, s};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CHAIR;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	{
		// Sofa.
		entity sofa = create_entity(world);

		Transform* transform = mix_transform(world, sofa);
		transform->translation = (vec3){3.0f, 0.0f, 1.0f};
		quat_from_euler(&transform->rotation, 0.0f, -60.0f, 0.0f);

		Collide* collide = mix_collide(world, sofa);
		collide->dynamic = false;
		collide->layers = LAYER_NONE;
		collide->mask = LAYER_PLAYER;
		collide->aabb.size = (vec3){1.0f, 3.0f, 1.0f};

		Trigger* trigger = mix_trigger(world, sofa);
		trigger->action = ACTION_TRIGGER_PLAY;
		trigger->mask = LAYER_PLAYER;

		{
			entity mesh = create_entity(world);
			transform->children[0] = mesh;

			Transform* mesh_transform = mix_transform(world, mesh);
			mesh_transform->parent = sofa;

			RenderColoredUnlit* mesh_render = mix_render_colored_unlit(world, mesh);
			mesh_render->material = MAT_COLORED_UNLIT;
			mesh_render->mesh = MESH_SOFA;
			mesh_render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
		}
	}

	{
		// Lamp.
		entity lamp = create_entity(world);

		Transform* lamp_transform = mix_transform(world, lamp);
		lamp_transform->translation = (vec3){-0.5f, 0.0f, 0.2f};

		RenderColoredUnlit* lamp_render = mix_render_colored_unlit(world, lamp);
		lamp_render->material = MAT_COLORED_UNLIT;
		lamp_render->mesh = MESH_LAMP;
		lamp_render->color = (vec4){0.88f, 0.32f, 0.4f, 1.0f};

		{
			// Light.
			entity light = create_entity(world);
			lamp_transform->children[0] = light;

			Transform* light_transform = mix_transform(world, light);
			light_transform->translation = (vec3){0.0f, 1.5f, 0.0f};
			light_transform->parent = lamp;

			LightPoint* light_point = mix_light_point(world, light);
			light_point->color = (vec3){0.9f, 0.9f, 0.3f};
			light_point->range = 2.0f;
		}
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
