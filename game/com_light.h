#pragma once
#include "../common/entity.h"
#include "../common/matrix.h"

enum light_kind {
	LIGHT_OFF,
	LIGHT_POINT,
	LIGHT_SPOT,
};

typedef struct light_point {
	enum light_kind kind;
	vec3 color;
	float range;
} LightPoint;

typedef struct light_spot {
	enum light_kind kind;
	vec3 color;
	float range;
	float angle;
} LightSpot;

typedef union light {
	enum light_kind kind;
	LightPoint point;
	LightSpot spot;
} Light;

struct world;
LightPoint* mix_light_point(struct world* world, entity entity);
LightSpot* mix_light_spot(struct world* world, entity entity);
