#include "com_light.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

Light* mix_light_directional(struct world* world, entity entity)
{
	Light* light = xmalloc(sizeof(*light));
	*light = (Light){
			.kind = LIGHT_DIRECTIONAL,
			.color = {1.0, 1.0, 1.0},
			.intensity = 1.0,
	};

	world->signature[entity] |= HAS_LIGHT;
	return world->light[entity] = light;
}

Light* mix_light_point(struct world* world, entity entity)
{
	Light* light = xmalloc(sizeof(*light));
	*light = (Light){
			.kind = LIGHT_POINT,
			.color = {1.0, 1.0, 1.0},
			.intensity = 1.0,
	};

	world->signature[entity] |= HAS_LIGHT;
	return world->light[entity] = light;
}
