#include <stdlib.h>
#include <time.h>

#include "blu_camera.h"
#include "com_transform.h"
#include "com_render.h"
#include "index.h"
#include "world.h"

void scene_cube(struct world* world)
{
	srand(time(NULL));

	{
		// Camera
		entity camera = blueprint_camera(world);
	}

	{
		// Cube
		entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation.z = -5.0;

		RenderColoredUnlit* render = mix_render_colored_unlit(world, entity);
		render->material = MAT_COLORED_UNLIT;
		render->mesh = MESH_CUBE;
		render->color.x = 0.32;
		render->color.y = 0.4;
		render->color.z = 0.88;
	}
}
