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
		transform->translation[2] = -5.0;

		RenderBasicColored* render = mix_render_basic_colored(world, entity);
		render->material = MAT_BASIC_COLORED;
		render->mesh = MESH_CUBE;
		render->color[0] = 0.32;
		render->color[1] = 0.4;
		render->color[2] = 0.88;
	}
}