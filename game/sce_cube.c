#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "../common/entity.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

Entity blueprint_camera_display(struct world* world);

void scene_cube(struct world* world)
{
	srand((uint32_t)time(NULL));

	{
		// Camera
		blueprint_camera_display(world);
	}

	{
		// Cube
		Entity entity = create_entity(world);

		Transform* transform = mix_transform(world, entity);
		transform->translation.z = -5.0;

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, entity);
		render->material = MAT_TEXTURED_UNLIT;
		render->texture = TEX_CHECKER;
		render->mesh = MESH_CUBE;
	}
}
