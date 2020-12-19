#include "com_mimic.h"

#include "../common/malloc.h"
#include "world.h"

Mimic* mix_mimic(struct world* world, Entity entity)
{
	Mimic* mimic = xmalloc(sizeof(*mimic));
	*mimic = (Mimic){
			.movement_stiffness = 0.1f,
			.rotation_stiffness = 0.1f,
	};

	world->signature[entity] |= HAS_MIMIC;
	return world->mimic[entity] = mimic;
}
