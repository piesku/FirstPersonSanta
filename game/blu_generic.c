#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "world.h"

entity blueprint_generic(struct world* world)
{
	entity root = create_entity(world);

	mix_transform(world, root);

	Collide* collide = mix_collide(world, root);
	collide->dynamic = false;
	collide->layers = LAYER_TERRAIN;
	collide->mask = LAYER_NONE;
	collide->aabb.size = (vec3){1.0f, 3.0f, 1.0f};

	RenderColoredUnlit* render = mix_render_colored_unlit(world, root);
	render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};
	render->material = MAT_COLORED_UNLIT;

	return root;
}
