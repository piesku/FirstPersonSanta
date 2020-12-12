#include <stdbool.h>
#include <stdint.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_rigid_body.h"
#include "com_shoot.h"
#include "com_transform.h"
#include "world.h"

Entity blueprint_gift(struct world* world);

static int32_t QUERY = HAS_TRANSFORM | HAS_SHOOT;

static inline void update(struct world* world, Entity entity, float delta)
{
	Shoot* shoot = world->shoot[entity];
	Transform* shooter_transform = world->transform[entity];

	shoot->since_last += delta;

	if (shoot->trigger) {
		shoot->trigger = false;
		if (shoot->since_last > shoot->frequency) {
			shoot->since_last = 0;

			size_t projectile = blueprint_gift(world);

			Transform* transform = world->transform[projectile];
			mat4_get_translation(&transform->translation, &shooter_transform->world);
			mat4_get_rotation(&transform->rotation, &shooter_transform->world);

			RigidBody* rigid_body = world->rigid_body[projectile];
			rigid_body->acceleration.z = 500.0;
		}
	}
}

void sys_shoot(struct world* world, float delta)
{
	for (Entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i, delta);
		}
	}
}
