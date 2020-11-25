#include "com_render.h"

#include "../common/malloc.h"
#include "../common/matrix.h"
#include "world.h"

RenderBasicColored* mix_render_basic_colored(struct world* world, entity entity)
{
	Render* render = xmalloc(sizeof(*render));
	*render = (Render){
			.basic_colored = {
					.kind = RENDER_BASIC_COLORED,
					.color = {0.0, 0.0, 0.0, 1.0},
			},
	};

	world->signature[entity] |= HAS_RENDER;
	world->render[entity] = render;
	return &render->basic_colored;
}

RenderBasicTextured* mix_render_basic_textured(struct world* world, entity entity)
{
	Render* render = xmalloc(sizeof(*render));
	*render = (Render){
			.basic_textured = {
					.kind = RENDER_BASIC_TEXTURED,

			}};

	world->signature[entity] |= HAS_RENDER;
	world->render[entity] = render;
	return &render->basic_textured;
}

RenderDiffuse* mix_render_diffuse(struct world* world, entity entity)
{
	Render* render = xmalloc(sizeof(*render));
	*render = (Render){
			.diffuse = {
					.kind = RENDER_DIFFUSE,
					.color = {0.0, 0.0, 0.0, 1.0},
			},
	};

	world->signature[entity] |= HAS_RENDER;
	world->render[entity] = render;
	return &render->diffuse;
}
