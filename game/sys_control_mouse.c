#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"

#include "client.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

static int QUERY = HAS_TRANSFORM | HAS_CONTROL_PLAYER;
static const vec3 AXIS_X = {1.0f, 0.0f, 0.0f};
static const vec3 AXIS_Y = {0.0f, 1.0f, 0.0f};

static inline void update(struct client* client, struct world* world, entity entity, float delta)
{
	ControlPlayer* control = world->control_player[entity];
	Transform* transform = world->transform[entity];

	quat rotation;

	if (control->yaw && client->input_delta.mouse_x) {
		// Scale the mouse input by the sensitivity.
		float amount = client->input_delta.mouse_x * control->yaw;

		// Treat the pixels traveled by the mouse in this frame as literal Euler
		// angles. This happens to work well and gives the mouse control an
		// instant and precise feel. Note that the rotation won't be passed to
		// sys_move; instead it's applied here and ignores Move.RotationSpeed on
		// purpose.
		quat_from_axis(&rotation, &AXIS_Y, -amount * DEG_TO_RAD);

		// Yaw is pre-multiplied, i.e. applied relative to the entity's local
		// space; the Y axis is not affected by its current orientation.
		quat_multiply(&transform->rotation, rotation, transform->rotation);
		transform->dirty = true;
	}

	if (control->pitch && client->input_delta.mouse_y) {
		float amount = client->input_delta.mouse_y * control->pitch;
		quat_from_axis(&rotation, &AXIS_X, amount * DEG_TO_RAD);

		// Pitch is post-multiplied, i.e. applied relative to the entity's self
		// space; the X axis is always aligned with its left and right sides.
		quat_multiply(&transform->rotation, transform->rotation, rotation);
		transform->dirty = true;
	}
}

void sys_control_mouse(struct client* client, struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i, delta);
		}
	}
}
