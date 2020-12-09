#include "com_light.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

LightPoint* mix_light_point(struct world* world, entity entity)
{
	Light* light = xmalloc(sizeof(*light));
	*light = (Light){
			.point = {
					.kind = LIGHT_POINT,
					.color = {1.0, 1.0, 1.0},
					.range = 1.0,
			}};

	world->signature[entity] |= HAS_LIGHT;
	world->light[entity] = light;
	return &light->point;
}

LightSpot* mix_light_spot(struct world* world, entity entity)
{
	Light* light = xmalloc(sizeof(*light));
	*light = (Light){
			.spot = {
					.kind = LIGHT_SPOT,
					.color = {1.0, 1.0, 1.0},
					.range = 1.0,
					.angle = PI / 3.0,
			}};

	world->signature[entity] |= HAS_LIGHT;
	world->light[entity] = light;
	return &light->spot;
}
