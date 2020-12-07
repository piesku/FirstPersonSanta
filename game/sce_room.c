#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_player(struct world* world);
entity blueprint_gift(struct world* world);

void scene_room(struct world* world)
{
	// Scale for all furniture.
	float s = 3.0;

	{
		entity camera = blueprint_camera_player(world);
		Transform* transform = world->transform[camera];
		transform->translation = (vec3){0.0, 1.7, 5.0};

		Collide* collide = mix_collide(world, camera);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
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

	{
		// Chair.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.0, 0.0, 0.0};
		transform->rotation = (quat){0.0, 1.0, 0.0, 0.0};
		transform->scale = (vec3){s, s, s};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CHAIR;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}

	{
		// Sofa.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.8, 0.0, 0.5};
		transform->scale = (vec3){s, s, s};
		quat_from_euler(&transform->rotation, 0, 120, 0);

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_SOFA;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}

	{
		// Lamp.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){-0.5, 0.0, 0.2};
		transform->scale = (vec3){s, s, s};
		quat_from_euler(&transform->rotation, 0, -130, 0);

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_LAMP;
		render->color = (vec4){0.88, 0.32, 0.4, 1.0};
	}

	{
		// Gift.
		entity entity = blueprint_gift(world);

		Transform* transform = world->transform[entity];
		transform->translation = (vec3){0.5, 0.25, 1.5};
		quat_from_euler(&transform->rotation, 0, -65, 0);
	}

	{
		// Building 1.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){-5.0, 0.0, -8.0};
		transform->scale = (vec3){10.0, 20.0, 10.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}

	{
		// Building 2.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){10.0, 0.0, -15.0};
		transform->scale = (vec3){50.0, 40.0, 10.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}
}