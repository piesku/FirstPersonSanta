#include <stdbool.h>
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"

#include "client.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_shoot.h"
#include "com_transform.h"
#include "world.h"

static int QUERY = HAS_MOVE | HAS_CONTROL_PLAYER;

static inline void update(struct client* client, struct world* world, Entity entity)
{
	ControlPlayer* control = world->control_player[entity];
	Move* move = world->move[entity];

	if (control->move) {
		move->direction = (vec3){0, 0, 0};

		if (client->input_state.key_w) {
			move->direction.z += 1;
			move->dirty |= MOVE_DIRTY_DIRECTION;
		}

		if (client->input_state.key_s) {
			move->direction.z -= 1;
			move->dirty |= MOVE_DIRTY_DIRECTION;
		}

		if (client->input_state.key_a) {
			move->direction.x += 1;
			move->dirty |= MOVE_DIRTY_DIRECTION;
		}

		if (client->input_state.key_d) {
			move->direction.x -= 1;
			move->dirty |= MOVE_DIRTY_DIRECTION;
		}
	}

	if (control->yaw) {
		if (client->input_state.arrow_left) {
			move->local_rotation = (quat){0, 1, 0, 0};
			move->dirty |= MOVE_DIRTY_LOCAL_ROTATION;
		}

		if (client->input_state.arrow_right) {
			move->local_rotation = (quat){0, -1, 0, 0};
			move->dirty |= MOVE_DIRTY_LOCAL_ROTATION;
		}
	}

	if (control->pitch) {
		if (client->input_state.arrow_up) {
			move->self_rotation = (quat){-1, 0, 0, 0};
			move->dirty |= MOVE_DIRTY_SELF_ROTATION;
		}

		if (client->input_state.arrow_down) {
			move->self_rotation = (quat){1, 0, 0, 0};
			move->dirty |= MOVE_DIRTY_SELF_ROTATION;
		}
	}

	if (control->shoot
			&& world->signature[entity] & HAS_SHOOT
			&& client->input_state.key_space) {
		Shoot* shoot = world->shoot[entity];
		shoot->trigger = true;
	}
}

void sys_control_keyboard(struct client* client, struct world* world)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i);
		}
	}
}
