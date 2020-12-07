#include "com_control_player.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

ControlPlayer* mix_control_player(struct world* world, entity entity)
{
	ControlPlayer* control = xmalloc(sizeof(*control));
	*control = (ControlPlayer){0};

	world->signature[entity] |= HAS_CONTROL_PLAYER;
	return world->control_player[entity] = control;
}
