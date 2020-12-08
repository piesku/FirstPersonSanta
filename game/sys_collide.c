#include <stdint.h>

#include "../common/aabb.h"
#include "../common/entity.h"
#include "../common/matrix.h"

#include "com_collide.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_COLLIDE;

static inline void check_for_collision(Collide* collider, Collide* other)
{
	int32_t collider_can_intersect = collider->mask & other->layers;
	int32_t other_can_intersect = other->mask & collider->layers;

	if (collider_can_intersect || other_can_intersect) {
		if (intersect_aabb(&collider->aabb, &other->aabb)) {
			vec3 hit;
			penetrate_aabb(&hit, &collider->aabb, &other->aabb);
			if (collider_can_intersect && collider->count < MAX_COLLISIONS) {
				collider->collisions[collider->count] = (struct collision){
						.other = other->entity,
						.hit = {hit.x, hit.y, hit.z},
				};
				collider->count++;
			}
			if (other_can_intersect && other->count < MAX_COLLISIONS) {
				other->collisions[other->count] = (struct collision){
						.other = collider->entity,
						.hit = {-hit.x, -hit.y, -hit.z},
				};
				other->count++;
			}
		}
	}
}

void sys_collide(struct world* world)
{
	// Set up colliders.
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Transform* transform = world->transform[i];
			Collide* collide = world->collide[i];

			if (collide->entity == 0) {
				// It's a new collider.
				collide->entity = i;
				compute_aabb_without_scale(&transform->world, &collide->aabb);
			} else if (collide->dynamic) {
				compute_aabb_without_scale(&transform->world, &collide->aabb);
			}

			// Reset the collision count in this frame.
			collide->count = 0;
		}
	}

	// Check each collider for collisions with other colliders.
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			Collide* collide = world->collide[i];

			// Start with i + 1 so that each pair of colliders is checked only once.
			for (entity j = i + 1; j < MAX_ENTITIES; j++) {
				if ((world->signature[j] & QUERY) == QUERY) {
					Collide* other = world->collide[j];

					if (collide->dynamic || other->dynamic) {
						check_for_collision(collide, other);
					}
				}
			}
		}
	}
}
