#include "com_collide.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

Collide* mix_collide(struct world* world, entity entity)
{
	Collide* collide = xmalloc(sizeof(*collide));
	*collide = (Collide){
			.entity = 0,
			.dynamic = false,
			.layers = LAYER_NONE,
			.mask = LAYER_NONE,
			.aabb = {
					.size = {1.0f, 1.0f, 1.0f},
			},
			.count = 0,
	};

	world->signature[entity] |= HAS_COLLIDE;
	return world->collide[entity] = collide;
}
