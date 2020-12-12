#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

Entity blueprint_furniture(struct world* world)
{
	Entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);

	RenderColoredUnlit* root_render = mix_render_colored_unlit(world, root);
	root_render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};
	root_render->material = MAT_COLORED_UNLIT;

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

		//RenderColoredUnlit* collider_render = mix_render_colored_unlit(world, collider);
		//collider_render->color = (vec4){0, 1, 0, 1};
		//collider_render->material = MAT_COLORED_UNLIT;
		//collider_render->mesh = MESH_CUBE;
	}

	return root;
}

Entity blueprint_decoration(struct world* world)
{
	Entity root = create_entity(world);

	mix_transform(world, root);

	RenderColoredUnlit* root_render = mix_render_colored_unlit(world, root);
	root_render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};
	root_render->material = MAT_COLORED_UNLIT;

	return root;
}
