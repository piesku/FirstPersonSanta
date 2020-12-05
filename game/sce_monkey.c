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
		Transform* transform = world->transform[camera];
		transform->translation = (vec3){0.0, 2.0, 2.0};

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
	}

	{
		// Monkey
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.0, 2.0, 0.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_MONKEY;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}

	{
		// Building 1.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){-5.0, 0.0, -10.0};
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
		transform->translation = (vec3){10.0, 0.0, -30.0};
		transform->scale = (vec3){50.0, 40.0, 10.0};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}
}