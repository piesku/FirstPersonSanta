#include "com_trigger.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

Trigger* mix_trigger(struct world* world, Entity entity)
{
	Trigger* trigger = xmalloc(sizeof(*trigger));
	*trigger = (Trigger){0};

	world->signature[entity] |= HAS_TRIGGER;
	return world->trigger[entity] = trigger;
}
