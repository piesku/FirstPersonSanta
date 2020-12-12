#include "com_move.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

Move* mix_move(struct world* world, Entity entity)
{
	Move* move = xmalloc(sizeof(*move));
	*move = (Move){
			.movement_speed = 0,
			.rotation_speed = 0,
			.direction = {0},
			.local_rotation = {0, 0, 0, 1},
			.self_rotation = {0, 0, 0, 1},
			.dirty = MOVE_DIRTY_NONE,
	};

	world->signature[entity] |= HAS_MOVE;
	return world->move[entity] = move;
}
