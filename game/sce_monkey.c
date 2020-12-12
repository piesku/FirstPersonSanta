#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

Entity blueprint_camera_player(struct world* world);

void scene_monkey(struct world* world)
{
	{
		Entity camera = blueprint_camera_player(world);
		Transform* transform = world->transform[camera];
		transform->translation = (vec3){0.0, 2.0, 2.0};

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

	{
		// Monkey
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){0.0f, 2.0f, 0.0f};
		transform->scale = (vec3){2.0f, 2.0f, 2.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_MONKEY;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	{
		// Building 1.
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){-5.0f, 0.0f, -10.0f};
		transform->scale = (vec3){10.0f, 20.0f, 10.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	{
		// Building 2.
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation = (vec3){10.0f, 0.0f, -30.0f};
		transform->scale = (vec3){50.0f, 40.0f, 10.0f};

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}
}
