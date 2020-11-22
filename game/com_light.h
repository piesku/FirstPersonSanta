#pragma once
#include "../common/entity.h"
#include "../common/matrix.h"

enum light_kind {
	LIGHT_OFF,
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
};

typedef struct light {
	enum light_kind kind;
	vec3 color;
	float intensity;
} Light;

struct world;
Light* mix_light_directional(struct world* world, entity entity);
Light* mix_light_point(struct world* world, entity entity);