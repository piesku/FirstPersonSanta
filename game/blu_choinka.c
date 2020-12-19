#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_light.h"
#include "com_mimic.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "com_trigger.h"
#include "world.h"

Entity blueprint_choinka(struct world* world)
{
	Entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);

	RenderColoredUnlit* root_render = mix_render_colored_unlit(world, root);
	root_render->material = MAT_COLORED_UNLIT;
	root_render->mesh = MESH_CHOINKA;
	root_render->color = (vec4){0.45f, 0.45f, 0.45f, 1.0f};
	root_render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};

	{
		// Collider must be the first child.
		Entity collider = create_entity(world);
		entity_list_push(&root_transform->children, collider);

		Transform* collider_transform = mix_transform(world, collider);
		collider_transform->parent = root;
		collider_transform->scale = (vec3){1.0f, 2.5f, 1.0f};

		Collide* collider_collide = mix_collide(world, collider);
		collider_collide->dynamic = true;
		collider_collide->layers = LAYER_TERRAIN;
		collider_collide->mask = LAYER_MOVABLE;
		collider_collide->aabb.size = (vec3){1.31f, 2.5f, 1.52f};

		RigidBody* collider_rigid_body = mix_rigid_body(world, collider);
		collider_rigid_body->kind = RIGID_STATIC;

		Trigger* choinka_trigger = mix_trigger(world, collider);
		choinka_trigger->action = ACTION_TRIGGER_CHOINKA;
		choinka_trigger->mask = LAYER_MOVABLE;
	}

	{
		// Target must me second child
		Entity target = create_entity(world);
		Transform* target_transform = mix_transform(world, target);
		entity_list_push(&root_transform->children, target);
		target_transform->translation = (vec3){0};

		Mimic* mimic = mix_mimic(world, root);
		mimic->target = target;
	}

	return root;
}
