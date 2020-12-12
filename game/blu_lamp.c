#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_light.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

Entity blueprint_lamp(struct world* world)
{
	Entity root = create_entity(world);

	Transform* lamp_transform = mix_transform(world, root);

	Collide* collide = mix_collide(world, root);
	collide->dynamic = false;
	collide->layers = LAYER_TERRAIN;
	collide->mask = LAYER_NONE;
	collide->aabb.size = (vec3){1.0f, 3.0f, 1.0f};

	RenderColoredUnlit* lamp_render = mix_render_colored_unlit(world, root);
	lamp_render->material = MAT_COLORED_UNLIT;
	lamp_render->mesh = MESH_LAMP_ROUND_FLOOR;
	lamp_render->color = (vec4){0.9f, 0.3f, 0.4f, 1.0f};

	{
		// Light.
		Entity light = create_entity(world);
		entity_list_push(&lamp_transform->children, light);

		Transform* light_transform = mix_transform(world, light);
		light_transform->translation = (vec3){0.0f, 2.0f, 0.0f};
		quat_from_euler(&light_transform->rotation, 90.0f, 0.0f, 0.0f);
		light_transform->parent = root;

		LightSpot* light_spot = mix_light_spot(world, light);
		light_spot->color = (vec3){0.9f, 0.9f, 0.3f};
		light_spot->range = 3.0f;
		light_spot->angle = PI / 3.0f;
	}

	return root;
}
