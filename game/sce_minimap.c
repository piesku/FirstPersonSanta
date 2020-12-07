#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_player(struct world* world);
entity blueprint_camera_minimap(struct world* world);

void scene_minimap(struct world* world)
{
	srand((uint32_t)time(NULL));

	{
		// Main camera.
		entity entity = blueprint_camera_player(world);

		Transform* transform = world->transform[entity];
		transform->translation = (vec3){0.0, 0.0, 5.0};
	}

	{
		// Checker cube.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		vec3_set(&transform->translation, 0, 0, 0);
		quat_from_euler(&transform->rotation, -45, 45, 0);

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, entity);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_CUBE;
		render->texture = TEX_CHECKER;
	}

	{
		// Minimap camera.
		entity entity = blueprint_camera_minimap(world);

		Transform* transform = world->transform[entity];
		vec3_set(&transform->translation, 0, 5, 0);
		quat_from_euler(&transform->rotation, 90, 180, 0);
	}

	{
		// Minimap quad.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		vec3_set(&transform->translation, 2, 0, 0);
		quat_from_euler(&transform->rotation, -45, 0, 0);

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, entity);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_QUAD;
		render->texture = TEX_MINIMAP_RGBA;
	}
}