#include <stdlib.h>
#include <time.h>

#include "blu_camera.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

void scene_physics(struct world* world)
{
	srand(time(NULL));

	{
		entity entity = blueprint_camera(world);
		world->transform[entity]->translation = (vec3){.x = 0.0, .y = 2.0, .z = 50.0};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
		collide->aabb.size = (vec3){.x = 2.0f, .y = 2.0f, .z = 2.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_KINEMATIC;
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->scale = (vec3){20.0, 1.0, 20.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};

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
