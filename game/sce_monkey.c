#include <stdlib.h>
#include <time.h>

#include "blu_camera.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

void scene_monkey(struct world* world)
{
	{
		entity camera = blueprint_camera_player(world);
		world->transform[camera]->translation[0] = 0.0;
		world->transform[camera]->translation[1] = 2.0;
		world->transform[camera]->translation[2] = 2.0;

		Collide* collide = mix_collide(world, camera);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[1] = -50.0;
		transform->scale[0] = 100.0;
		transform->scale[1] = 100.0;
		transform->scale[2] = 100.0;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}

	{
		// Monkey
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = 0.0;
		transform->translation[1] = 2.0;
		transform->translation[2] = 0.0;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_MONKEY;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}

	{
		// Building 1.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = -5.0;
		transform->translation[1] = 0.0;
		transform->translation[2] = -10.0;
		transform->scale[0] = 10.0;
		transform->scale[1] = 20.0;
		transform->scale[2] = 10.0;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}

	{
		// Building 2.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = 10.0;
		transform->translation[1] = 0.0;
		transform->translation[2] = -30.0;
		transform->scale[0] = 50.0;
		transform->scale[1] = 40.0;
		transform->scale[2] = 10.0;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}
}