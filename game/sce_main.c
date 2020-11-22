#include <stdlib.h>
#include <time.h>

#include "blu_camera.h"
#include "canvas.h"
#include "com_transform.h"
#include "com_render.h"
#include "world.h"

void scene_main(struct world* world)
{
	srand(time(NULL));

	{
		entity camera = blueprint_camera(world);
		world->transform[camera]->translation[0] = 0.0;
		world->transform[camera]->translation[1] = 2.0;
		world->transform[camera]->translation[2] = 0.0;
	}

	{
		// Ground
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[1] = -50.0;
		transform->scale[0] = 100.0;
		transform->scale[1] = 100.0;
		transform->scale[2] = 100.0;

		RenderBasicColored* render = mix_render_basic_colored(world, entity);
		render->material = MAT_BASIC_COLORED;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}

	for (int i = 0; i < 3; i++) {
		// Building
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = rand() % 100 - 50;
		transform->translation[1] = 0;
		transform->translation[2] = rand() % 100 - 50;
		transform->scale[0] = rand() % 45 + 5;
		transform->scale[1] = rand() % 95 + 5;
		transform->scale[2] = rand() % 45 + 5;

		RenderBasicColored* render = mix_render_basic_colored(world, entity);
		render->material = MAT_BASIC_COLORED;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}
}