#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "actions.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "com_trigger.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_player(struct world* world);

void scene_bounce(struct world* world)
{
	srand(time(NULL));

	{
		entity entity = blueprint_camera_player(world);
		Transform* transform = world->transform[entity];
		transform->translation = (vec3){0.0, 100.0, 0.0};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
		collide->aabb.size = (vec3){2.0f, 2.0f, 2.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_DYNAMIC;
		rigid_body->bounciness = 0.1f;
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation.y = -50.0;
		transform->scale = (vec3){100.0, 100.0, 100.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = false;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_NONE;
		collide->aabb.size = (vec3){100.0f, 100.0f, 100.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_STATIC;
	}

	// Trampolines.
	for (int i = 0; i < 10; i++) {
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){
				.x = rand() % 80 - 40,
				.y = 0.0f,
				.z = rand() % 80 - 40,
		};
		transform->scale = (vec3){10.0, 0.1, 10.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.88, 0.4, 1.0};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = false;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_PLAYER;
		collide->aabb.size = (vec3){10.0f, 0.1f, 10.0f};

		RigidBody* rigid_body = mix_rigid_body(world, entity);
		rigid_body->kind = RIGID_STATIC;

		Trigger* trigger = mix_trigger(world, entity);
		trigger->action = ACTION_TRIGGER_BOUNCE;
	}
}
