#include <stdlib.h>
#include <time.h>

#include "blu_camera.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

void scene_collide(struct world* world)
{
	srand(time(NULL));

	{
		entity camera = blueprint_camera(world);
		world->transform[camera]->translation[0] = 0.0;
		world->transform[camera]->translation[1] = 0.0;
		world->transform[camera]->translation[2] = 0.0;

		Collide* collide = mix_collide(world, camera);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
	}

	for (int i = 0; i < 200; i++) {
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = (rand() % 10 - 5) * 0.9;
		transform->translation[1] = (rand() % 10 - 5) * 0.9;
		transform->translation[2] = (rand() % 10 - 5) * 0.9;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color[0] = (rand() % 100) / 100.0f;
		render->color[1] = (rand() % 100) / 100.0f;
		render->color[2] = (rand() % 100) / 100.0f;

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_TERRAIN | LAYER_PLAYER;
	}
}