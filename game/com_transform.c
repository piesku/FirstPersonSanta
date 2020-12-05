#include "com_transform.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"


Transform* mix_transform(struct world* world, entity entity)
{
	Transform* transform = xmalloc(sizeof(*transform));
	*transform = (Transform){
			.world = {0},
			.self = {0},
			.translation = {0, 0, 0},
			.rotation = {0, 0, 0, 1},
			.scale = {1, 1, 1},
			.dirty = true,
	};

	mat4_identity(&transform->world);
	mat4_identity(&transform->self);

	world->signature[entity] |= HAS_TRANSFORM;
	return world->transform[entity] = transform;
}
