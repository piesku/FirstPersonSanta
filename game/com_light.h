#pragma once
#include "../common/entity.h"
#include "../common/matrix.h"

enum light_kind {
	LIGHT_OFF,
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
};

typedef struct light_directional {
	enum light_kind kind;
	vec3 color;
	float intensity;
} LightDirectional;

typedef struct light_point {
	enum light_kind kind;
	vec3 color;
	float intensity;
} LightPoint;

typedef union light {
	enum light_kind kind;
	LightDirectional directional;
	LightPoint point;
} Light;

struct world;
LightDirectional* mix_light_directional(struct world* world, entity entity);
LightPoint* mix_light_point(struct world* world, entity entity);