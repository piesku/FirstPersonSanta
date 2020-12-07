#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_display(struct world* world);

void scene_physics(struct world* world)
{
	srand((uint32_t)time(NULL));

	{
		entity entity = blueprint_camera_display(world);
		world->transform[entity]->translation = (vec3){0.0, 2.0, 50.0};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
		collide->aabb.size = (vec3){2.0f, 2.0f, 2.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_KINEMATIC;
		rigid_body->bounciness = 0.1f;
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->scale = (vec3){20.0f, 1.0f, 20.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = false;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_NONE;
		collide->aabb.size = (vec3){20.0f, 1.0f, 20.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_STATIC;
	}

	for (int i = 0; i < 200; i++) {
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){
				.x = (rand() % 10 - 5) * 0.9f,
				.y = (float)i + 20.0f,
				.z = (rand() % 10 - 5) * 0.9f,
		};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){
				.x = (rand() % 100) / 100.0f,
				.y = (rand() % 100) / 100.0f,
				.z = (rand() % 100) / 100.0f,
				.w = 1.0,
		};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_MOVABLE;
		collide->mask = LAYER_TERRAIN | LAYER_MOVABLE | LAYER_PLAYER;

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_DYNAMIC;
	}
}
