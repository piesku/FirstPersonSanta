#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"
#include "com_collide.h"
#include "com_rigid_body.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_RIGID_BODY;
static const float GRAVITY = -9.81f;

static inline void update(struct world* world, entity entity, float delta)
{
	Transform* transform = world->transform[entity];
	RigidBody* rigid_body = world->rigid_body[entity];
	Collide* collide = world->collide[entity];

	// Temp vector used to compute the reflection off of a static body.
	vec3 a = {0};

	if (rigid_body->kind == RIGID_DYNAMIC) {
		bool has_collision = false;

		for (int8_t i = 0; i < collide->count; i++) {
			struct collision collision = collide->collisions[i];

			if (world->signature[collision.other] & HAS_RIGID_BODY) {
				has_collision = true;

				// Dynamic rigid bodies are only supported for top-level
				// entities. Thus, no need to apply the world → self → local
				// conversion to the collision response. Local space is world space.
				vec3_add(transform->translation, transform->translation, collision.hit);
				transform->dirty = true;

				// Assume mass = 1 for all rigid bodies. On collision,
				// velocities are swapped, unless the other body is a static
				// one (and behaves as if it had infinite mass).
				RigidBody* other_body = world->rigid_body[collision.other];
				switch (other_body->kind) {
					case RIGID_STATIC:
						// Compute the reflection vector as
						//   r = v - 2 * (v·n) * n
						// where
						//   v — the incident velocity vector
						//   n — the normal of the surface of reflection
						// Compute n.
						vec3_normalize(a, collision.hit);
						// Compute - 2 * (v·n) * n.
						vec3_scale(a, a, -2 * vec3_dot(rigid_body->velocity_integrated, a));
						vec3_add(rigid_body->velocity_resolved, rigid_body->velocity_integrated, a);
						break;
					case RIGID_DYNAMIC:
					case RIGID_KINEMATIC:
						vec3_copy(rigid_body->velocity_resolved, other_body->velocity_integrated);
						break;
				}

				// Collisions aren't 100% elastic.
				vec3_scale(rigid_body->velocity_resolved, rigid_body->velocity_resolved, 0.8);

				if (collision.hit[1] > 0 && rigid_body->velocity_resolved[1] < 1) {
					// Collision from the bottom stops the downward movement.
					rigid_body->velocity_resolved[1] = 0;
				}
			}
		}

		if (!has_collision) {
			vec3_copy(rigid_body->velocity_resolved, rigid_body->velocity_integrated);
		}
	}
}

void sys_physics_resolve(struct client* client, struct world* world, float delta)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i, delta);
		}
	}
}
