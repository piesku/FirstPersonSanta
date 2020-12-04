#include <stdlib.h>
#include <time.h>

#include "blu_camera.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

void scene_main(struct world* world)
{
	srand(time(NULL));

	{
		entity camera = blueprint_camera(world);
		world->transform[camera]->translation = (vec3){0.0, 2.0, 0.0};

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

	for (int i = 0; i < 3; i++) {
		// Building
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){
				.x = rand() % 100 - 50,
				.y = 0,
				.z = rand() % 100 - 50,
		};
		transform->scale = (vec3){
				.x = rand() % 45 + 5,
				.y = rand() % 95 + 5,
				.z = rand() % 45 + 5,
		};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32, 0.4, 0.88, 1.0};
	}

	{
		// Textured cube.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){1, 2, -10};

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, entity);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_CUBE;
		render->texture = TEX_CHECKER;

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = false;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_PLAYER;
	}
}
