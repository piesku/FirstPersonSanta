#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

Entity blueprint_gift(struct world* world)
{
	Entity root = create_entity(world);

	Transform* transform = mix_transform(world, root);

	Collide* collide = mix_collide(world, root);
	collide->dynamic = true;
	collide->layers = LAYER_MOVABLE;
	collide->mask = LAYER_TERRAIN | LAYER_MOVABLE;
	collide->aabb.size = (vec3){0.2f, 0.3f, 0.2f};

	RigidBody* rigid_body = mix_rigid_body(world, root);
	rigid_body->kind = RIGID_DYNAMIC;
	rigid_body->bounciness = 0.8f;

	{
		Entity mesh = create_entity(world);
		entity_list_push(&transform->children, mesh);

		Transform* mesh_transform = mix_transform(world, mesh);
		mesh_transform->scale = (vec3){0.5f, 0.5f, 0.5f};
		mesh_transform->parent = root;

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, mesh);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_GIFT;
		render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};
		render->texture = TEX_WRAPPING1;
		render->texscale = (vec2){25.0f, 25.0f};
	}

	return root;
}
