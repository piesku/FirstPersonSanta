#include "../common/entity.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"

entity blueprint_gift(struct world* world)
{
	entity container = create_entity(world);

	Transform* transform = mix_transform(world, container);

	Collide* collide = mix_collide(world, container);
	collide->dynamic = true;
	collide->layers = LAYER_MOVABLE;
	collide->mask = LAYER_TERRAIN | LAYER_MOVABLE;
	collide->aabb.size = (vec3){0.5, 0.5, 0.5};

	RigidBody* rigid_body = mix_rigid_body(world, container);
	rigid_body->kind = RIGID_DYNAMIC;
	rigid_body->bounciness = 0.8;

	{
		entity mesh = create_entity(world);
		transform->children[0] = mesh;

		Transform* mesh_transform = mix_transform(world, mesh);
		mesh_transform->scale = (vec3){0.5, 0.5, 0.5};
		mesh_transform->parent = container;

		RenderTexturedUnlit* render = mix_render_textured_unlit(world, mesh);
		render->material = MAT_TEXTURED_UNLIT;
		render->mesh = MESH_GIFT;
		render->color = (vec4){0.32, 0.58, 0.58, 1.0};
		render->texture = TEX_WRAPPING1;
		render->texscale = (vec2){25.0, 25.0};
	}

	return container;
}