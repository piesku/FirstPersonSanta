#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_RIGID_BODY;
static const float GRAVITY = -9.81f;

static inline void update(struct world* world, Entity entity, float delta)
{
	Transform* transform = world->transform[entity];
	RigidBody* rigid_body = world->rigid_body[entity];

	if (rigid_body->kind == RIGID_DYNAMIC) {
		vec3_copy(&rigid_body->velocity_integrated, &rigid_body->velocity_resolved);

		// Transform the acceleration into the world space.
		vec3_transform_direction(&rigid_body->acceleration, &rigid_body->acceleration, &transform->world);
		vec3_scale(&rigid_body->acceleration, &rigid_body->acceleration, delta);

		// Compute change to velocity, including the gravity.
		vec3_add(&rigid_body->velocity_integrated, &rigid_body->velocity_integrated, &rigid_body->acceleration);
		rigid_body->velocity_integrated.y += GRAVITY * delta;

		// Apply velocity to position.
		vec3 vel_delta = {0};
		vec3_scale(&vel_delta, &rigid_body->velocity_integrated, delta);
		vec3_add(&transform->translation, &transform->translation, &vel_delta);
		transform->dirty = true;

		// Reset force/acceleration.
		vec3_set(&rigid_body->acceleration, 0, 0, 0);
	}
}

void sys_physics_integrate(struct world* world, float delta)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i, delta);
		}
	}
}
