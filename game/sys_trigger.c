#include "actions.h"
#include "com_collide.h"
#include "com_transform.h"
#include "com_trigger.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_COLLIDE | HAS_TRIGGER;

static inline void update(struct client* client, struct world* world, entity entity)
{

	Collide* collide = world->collide[entity];
	Trigger* trigger = world->trigger[entity];

	for (int8_t i = 0; i < collide->count; i++) {
		struct collision* collision = &collide->collisions[i];
		dispatch(client, world,
				trigger->action,
				(union action_data){
						.trigger = {
								.collider = entity,
								.other = collision->other,
						},
				});
	}
}

void sys_trigger(struct client* client, struct world* world)
{

	// Check each collider for collisions with other colliders.
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(client, world, i);
		}
	}
}
