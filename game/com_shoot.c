#include "com_shoot.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

Shoot* mix_shoot(struct world* world, Entity entity)
{
	Shoot* shoot = xmalloc(sizeof(*shoot));
	*shoot = (Shoot){0};

	world->signature[entity] |= HAS_SHOOT;
	return world->shoot[entity] = shoot;
}
