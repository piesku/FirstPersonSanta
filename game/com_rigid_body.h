#pragma once
#include "../common/entity.h"
#include "../common/matrix.h"

// Assume mass = 1, which means that acceleration and force are numerically equal.

enum rigid_kind {
	RIGID_STATIC,
	RIGID_DYNAMIC,
	RIGID_KINEMATIC,
};

typedef struct rigid_body {
	enum rigid_kind kind;
	vec3 acceleration;
	vec3 velocity_integrated;
	vec3 velocity_resolved;
	vec3 last_position;
} RigidBody;

struct world;
RigidBody* mix_rigid_body(struct world* world, entity entity);