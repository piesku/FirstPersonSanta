#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"

#include "client.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

static int QUERY = HAS_MOVE | HAS_CONTROL_PLAYER;

static inline void update(struct client* client, struct world* world, entity entity, float delta)
{
	Move* move = world->move[entity];
	move->direction[0] = 0;

	if (client->input_state.arrow_left)
		move->direction[0] -= 1;

	if (client->input_state.arrow_right)
		move->direction[0] += 1;
}

void sys_control_keyboard(struct client* client, struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i, delta);
		}
	}
}
