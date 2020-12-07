#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_display(struct world* world);

void scene_collide(struct world* world)
{
	srand(time(NULL));

	{
		entity camera = blueprint_camera_display(world);
		world->transform[camera]->translation = (vec3){0.0, 0.0, 0.0};

		Collide* collide = mix_collide(world, camera);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
	}

	for (int i = 0; i < 200; i++) {
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){
				.x = (rand() % 10 - 5) * 0.9,
				.y = (rand() % 10 - 5) * 0.9,
				.z = (rand() % 10 - 5) * 0.9,
		};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){
				.x = (rand() % 100) / 100.0f,
				.y = (rand() % 100) / 100.0f,
				.z = (rand() % 100) / 100.0f,
				.w = 1.0f,
		};

		Collide* collide = mix_collide(world, entity);
		collide->dynamic = true;
		collide->layers = LAYER_TERRAIN;
		collide->mask = LAYER_TERRAIN | LAYER_PLAYER;
	}
}
