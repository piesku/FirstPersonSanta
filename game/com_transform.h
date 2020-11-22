#pragma once
#include <stdbool.h>

#include "../common/entity.h"
#include "../common/matrix.h"

#define MAX_CHILDREN 2

typedef struct transform {
	mat4 world;
	mat4 self;
	vec3 translation;
	quat rotation;
	vec3 scale;
	entity parent;
	entity children[MAX_CHILDREN];
	bool dirty;
} Transform;

struct world;
Transform* mix_transform(struct world* world, entity entity);
