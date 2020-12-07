#include "com_mimic.h"

#include "../common/malloc.h"
#include "world.h"

Mimic* mix_mimic(struct world* world, entity entity)
{
	Mimic* mimic = xmalloc(sizeof(*mimic));
	*mimic = (Mimic){
			.stiffness = 0.1,
	};

	world->signature[entity] |= HAS_MIMIC;
	return world->mimic[entity] = mimic;
}