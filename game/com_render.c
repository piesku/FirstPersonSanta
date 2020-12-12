#include "com_render.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

RenderColoredUnlit* mix_render_colored_unlit(struct world* world, Entity entity)
{
	Render* render = xmalloc(sizeof(*render));
	*render = (Render){
			.colored_unlit = {
					.kind = RENDER_COLORED_UNLIT,
					.color = {0.0, 0.0, 0.0, 1.0},
			},
	};

	world->signature[entity] |= HAS_RENDER;
	world->render[entity] = render;
	return &render->colored_unlit;
}

RenderColoredDiffuse* mix_render_colored_diffuse(struct world* world, Entity entity)
{
	Render* render = xmalloc(sizeof(*render));
	*render = (Render){
			.colored_diffuse = {
					.kind = RENDER_COLORED_DIFFUSE,
					.color = {0.0, 0.0, 0.0, 1.0},
			},
	};

	world->signature[entity] |= HAS_RENDER;
	world->render[entity] = render;
	return &render->colored_diffuse;
}

RenderTexturedUnlit* mix_render_textured_unlit(struct world* world, Entity entity)
{
	Render* render = xmalloc(sizeof(*render));
	*render = (Render){
			.textured_unlit = {
					.kind = RENDER_TEXTURED_UNLIT,
					.color = {1.0, 1.0, 1.0, 1.0},
					.texscale = {1.0, 1.0},
			}};

	world->signature[entity] |= HAS_RENDER;
	world->render[entity] = render;
	return &render->textured_unlit;
}
