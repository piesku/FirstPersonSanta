#include <stdbool.h>
#include <stdint.h>

#include "../common/matrix.h"
#include "com_mimic.h"
#include "com_transform.h"
#include "world.h"

static int32_t QUERY = HAS_TRANSFORM | HAS_MIMIC;

static inline void update(struct world* world, entity entity)
{
	Mimic* mimic = world->mimic[entity];

	// Follower must be a top-level transform.
	Transform* follower_transform = world->transform[entity];
	Transform* target_transform = world->transform[mimic->target];

	vec4 target_world_position;
	mat4_get_translation(&target_world_position, &target_transform->world);
	vec3_lerp(&follower_transform->translation,
			&follower_transform->translation, &target_world_position, mimic->stiffness);

	quat target_world_rotation;
	mat4_get_rotation(&target_world_rotation, &target_transform->world);
	quat_lerp(&follower_transform->rotation,
			&follower_transform->rotation, &target_world_rotation, mimic->stiffness);

	follower_transform->dirty = true;
}

void sys_mimic(struct world* world)
{
	for (entity i = 1; i < MAX_ENTITIES; i++) {
		if ((world->signature[i] & QUERY) == QUERY) {
			update(world, i);
		}
	}
}
