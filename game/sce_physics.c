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
		world->transform[entity]->translation.x = 0.0;
		world->transform[entity]->translation.y = 2.0;
		world->transform[entity]->translation.z = 50.0;

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
		collide->aabb.size.x = 2.0f;
		collide->aabb.size.y = 2.0f;
		collide->aabb.size.z = 2.0f;

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_KINEMATIC;
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->scale.x = 20.0;
		transform->scale.y = 1.0;
		transform->scale.z = 20.0;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = false;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_NONE;
		collide->aabb.size.x = 20.0f;
		collide->aabb.size.y = 1.0f;
		collide->aabb.size.z = 20.0f;

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_STATIC;
	}

	for (int i = 0; i < 200; i++) {
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation.x = (rand() % 10 - 5) * 0.9f;
		transform->translation.y = (float)i + 20.0f;
		transform->translation.z = (rand() % 10 - 5) * 0.9f;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color[0] = (rand() % 100) / 100.0f;
		render->color[1] = (rand() % 100) / 100.0f;
		render->color[2] = (rand() % 100) / 100.0f;

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_MOVABLE;
		collide->mask = LAYER_TERRAIN | LAYER_MOVABLE | LAYER_PLAYER;

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_DYNAMIC;
	}
}
