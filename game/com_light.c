#include "com_light.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

LightDirectional* mix_light_directional(struct world* world, entity entity)
{
	Light* light = xmalloc(sizeof(*light));
	*light = (Light){
			.directional = {
					.kind = LIGHT_DIRECTIONAL,
					.color = {1.0, 1.0, 1.0},
					.intensity = 1.0,
			}};

	world->signature[entity] |= HAS_LIGHT;
	world->light[entity] = light;
	return &light->directional;
}

LightPoint* mix_light_point(struct world* world, entity entity)
{
	Light* light = xmalloc(sizeof(*light));
	*light = (Light){
			.point = {
					.kind = LIGHT_POINT,
					.color = {1.0, 1.0, 1.0},
					.intensity = 1.0,
			}};

	world->signature[entity] |= HAS_LIGHT;
	world->light[entity] = light;
	return &light->point;
}
