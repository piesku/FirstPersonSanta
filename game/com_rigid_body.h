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
	float bounciness;
	// The acceleration to apply this frame, in self space. For best results
	// use with transform's scale = 1. The acceleration is zeroed every frame.
	vec3 acceleration;
	// The velocity vector in the world space, computed in
	// sys_physics_integrate from the velocity in the previous frame, this
	// frame's acceleration and the gravity.
	vec3 velocity_integrated;
	// The velocity vector in the world space after all collisions have been
	// resolved this frame.
	vec3 velocity_resolved;
	// The last position, used to compute the velocity of kinematic bodies.
	vec3 last_position;
} RigidBody;

struct world;
RigidBody* mix_rigid_body(struct world* world, entity entity);
