#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

Entity blueprint_camera_player(struct world* world);

void scene_main(struct world* world)
{
	srand((uint32_t)time(NULL));

	{
		Entity camera = blueprint_camera_player(world);
		world->transform[camera]->translation = (vec3){0.0, 2.0, 0.0};

		Collide* collide = mix_collide(world, camera);
		collide->dynamic = true;
		collide->layers = LAYER_PLAYER;
		collide->mask = LAYER_TERRAIN;
	}

	{
		// Ground
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation.y = -50.0f;
		transform->scale = (vec3){100.0f, 100.0f, 100.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	for (int i = 0; i < 3; i++) {
		// Building
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){
				.x = rand() % 100 - 50.0f,
				.y = 0.0f,
				.z = rand() % 100 - 50.0f,
		};
		transform->scale = (vec3){
				.x = rand() % 45 + 5.0f,
				.y = rand() % 95 + 5.0f,
				.z = rand() % 45 + 5.0f,
		};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}
}
