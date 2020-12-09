#include "../common/entity.h"
#include "com_collide.h"
#include "com_light.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

entity blueprint_lamp(struct world* world, vec3 translation, quat rotation)
{
	// Scale for all furniture.
	float s = 3.0f;

	entity lamp = create_entity(world);

	Transform* lamp_transform = mix_transform(world, lamp);
	lamp_transform->scale = (vec3){s, s, s};
	lamp_transform->translation = translation;
	lamp_transform->rotation = rotation;

	RenderColoredUnlit* lamp_render = mix_render_colored_unlit(world, lamp);
	lamp_render->material = MAT_COLORED_UNLIT;
	lamp_render->mesh = MESH_LAMP;
	lamp_render->color = (vec4){0.88f, 0.32f, 0.4f, 1.0f};

	{
		// Light.
		entity light = create_entity(world);
		lamp_transform->children[0] = light;

		Transform* light_transform = mix_transform(world, light);
		light_transform->translation = (vec3){0.0f, 0.12f, 0.0f};
		light_transform->parent = lamp;

		LightPoint* light_point = mix_light_point(world, light);
		light_point->color = (vec3){0.9f, 0.9f, 0.3f};
		light_point->range = 1.5f;
	}

	return lamp;
}
