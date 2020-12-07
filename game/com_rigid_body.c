#include "com_rigid_body.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

RigidBody* mix_rigid_body(struct world* world, entity entity)
{
	RigidBody* rigid_body = xmalloc(sizeof(*rigid_body));
	*rigid_body = (RigidBody){
			.kind = RIGID_DYNAMIC,
			.bounciness = 0.8f,
	};

	world->signature[entity] |= HAS_RIGID_BODY;
	return world->rigid_body[entity] = rigid_body;
}
