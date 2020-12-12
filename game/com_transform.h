#pragma once
#include <stdbool.h>

#include "../common/entity.h"
#include "../common/matrix.h"

typedef struct transform {
	mat4 world;
	mat4 self;
	vec3 translation;
	quat rotation;
	vec3 scale;
	Entity parent;
	struct entity_list children;
	bool dirty;
} Transform;

struct world;
Transform* mix_transform(struct world* world, Entity entity);
