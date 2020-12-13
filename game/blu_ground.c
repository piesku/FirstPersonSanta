#include "../common/entity.h"
#include "../common/matrix.h"

#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

Entity blueprint_ground(struct world* world)
{
	// Ground
	Entity root = create_entity(world);

	Transform* transform = mix_transform(world, root);
	transform->translation.y = -50;
	transform->scale = (vec3){1000, 100, 1000};

	RenderColoredUnlit* render = mix_render_colored_unlit(world, root);
	render->material = MAT_COLORED_UNLIT;
	render->mesh = MESH_CUBE;
	render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};

	Collide* collide = mix_collide(world, root);
	collide->dynamic = false;
	collide->layers = LAYER_TERRAIN;
	collide->mask = LAYER_NONE;

	RigidBody* rigid_body = mix_rigid_body(world, root);
	rigid_body->kind = RIGID_STATIC;

	return root;
}
