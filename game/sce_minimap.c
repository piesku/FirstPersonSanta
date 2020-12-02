#include <stdlib.h>
#include <time.h>

#include "../common/matrix.h"

#include "blu_camera.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

void scene_minimap(struct world* world)
{
	srand(time(NULL));

	{
		// Main camera.
		entity entity = blueprint_camera_display(world);

		Transform* transform = world->transform[entity];
		transform->translation[0] = 0.0;
		transform->translation[1] = 0.0;
		transform->translation[2] = 5.0;
	}

	{
		// Checker cube.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = 0;
		transform->translation[1] = 0;
		transform->translation[2] = 0;

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, entity);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_CUBE;
		render->texture = TEX_CHECKER;
	}

	{
		// Minimap camera.
		entity entity = blueprint_camera_framebuffer(world);

		Transform* transform = world->transform[entity];
		transform->translation[0] = 0.0;
		transform->translation[1] = 5.0;
		transform->translation[2] = 0.0;
		quat_from_euler(transform->rotation, 90, 0, 180);
	}

	{
		// Minimap quad.
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation[0] = 2;
		transform->translation[1] = 0;
		transform->translation[2] = 0;

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, entity);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_QUAD;
		render->texture = TEX_RENDER_RGBA;
	}
}