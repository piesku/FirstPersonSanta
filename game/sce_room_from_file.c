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
entity blueprint_camera_player(struct world* world);

void scene_room_from_file(struct world* world)
{

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

	load_scene_from_gltf(world, "scenes/scene2.gltf");
}
