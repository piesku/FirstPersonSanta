#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_light.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

Entity blueprint_choinka(struct world* world)
{
	Entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);

	RenderColoredUnlit* root_render = mix_render_colored_unlit(world, root);
	root_render->material = MAT_COLORED_UNLIT;
	root_render->mesh = MESH_CHOINKA;
	root_render->color = (vec4){0.22f, 0.48f, 0.33f, 1.0f};

	{
		// Collider must be the first child.
		Entity collider = create_entity(world);
		entity_list_push(&root_transform->children, collider);

		Transform* collider_transform = mix_transform(world, collider);
		collider_transform->parent = root;

		Collide* collider_collide = mix_collide(world, collider);
		collider_collide->dynamic = false;
		collider_collide->layers = LAYER_TERRAIN;
		collider_collide->mask = LAYER_NONE;

		RigidBody* collider_rigid_body = mix_rigid_body(world, collider);
		collider_rigid_body->kind = RIGID_STATIC;
	}

	{
		// Light.
		Entity light = create_entity(world);
		entity_list_push(&root_transform->children, light);

		Transform* light_transform = mix_transform(world, light);
		light_transform->translation = (vec3){0.0f, 2.0f, 0.0f};
		quat_from_euler(&light_transform->rotation, 90.0f, 0.0f, 0.0f);
		light_transform->parent = root;

		LightSpot* light_spot = mix_light_spot(world, light);
		light_spot->color = (vec3){0.9f, 0.0f, 0.0f};
		light_spot->range = 1.0f;
		light_spot->angle = PI / 3.0f;
	}

	return root;
}
