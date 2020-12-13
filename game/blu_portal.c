#include "../common/entity.h"
#include "../common/matrix.h"

#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "com_trigger.h"
#include "index.h"
#include "world.h"

Entity blueprint_portal(struct world* world)
{
	Entity root = create_entity(world);

	mix_transform(world, root);

	RenderColoredUnlit* render = mix_render_colored_unlit(world, root);
	render->material = MAT_COLORED_UNLIT;
	render->mesh = MESH_CUBE;
	render->color = (vec4){1, 0, 1, 1};

	Collide* collide = mix_collide(world, root);
	collide->dynamic = false;
	collide->layers = LAYER_TERRAIN;
	collide->mask = LAYER_PLAYER;

	Trigger* trigger = mix_trigger(world, root);
	trigger->action = ACTION_TRIGGER_PLAY;
	trigger->mask = LAYER_PLAYER;

	return root;
}
