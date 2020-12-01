#include <stdint.h>

#include "../common/matrix.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_RIGID_BODY;

static inline void update(struct world* world, entity entity, float delta)
{
	Transform* transform = world->transform[entity];
	RigidBody* rigid_body = world->rigid_body[entity];

	if (rigid_body->kind == RIGID_KINEMATIC) {
		vec3 current_position = {0};
		mat4_get_translation(&current_position, transform->world);
		vec3 movement = {0};
		vec3_subtract(&movement, current_position, rigid_body->last_position);

		// Compute velocity from this frame's movement.
		vec3_scale(&rigid_body->velocity_integrated, movement, 1 / delta);

		vec3_copy(&rigid_body->last_position, current_position);
	}
}

void sys_physics_kinematic(struct client* client, struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i, delta);
		}
	}
}
