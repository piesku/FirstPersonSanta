#pragma once
#include "../common/entity.h"
#include "../common/material.h"
#include "../common/matrix.h"
#include "../common/mesh.h"
#include "../common/texture.h"

#include "index.h"

enum render_kind {
	RENDER_COLORED_UNLIT,
	RENDER_COLORED_DIFFUSE,
	RENDER_TEXTURED_UNLIT,
};

typedef struct render_colored_unlit {
	enum render_kind kind;
	enum material_index material;
	enum mesh_index mesh;
	vec4 color;
} RenderColoredUnlit;

typedef struct render_colored_diffuse {
	enum render_kind kind;
	enum material_index material;
	enum mesh_index mesh;
	vec4 color;
} RenderColoredDiffuse;

typedef struct render_textured_unlit {
	enum render_kind kind;
	enum material_index material;
	enum mesh_index mesh;
	enum texture_index texture;
	vec2 texscale;
	vec4 color;
} RenderTexturedUnlit;

typedef union render {
	enum render_kind kind;
	RenderColoredUnlit colored_unlit;
	RenderColoredDiffuse colored_diffuse;
	RenderTexturedUnlit textured_unlit;
} Render;

struct world;
RenderColoredUnlit* mix_render_colored_unlit(struct world* world, Entity entity);
RenderColoredDiffuse* mix_render_colored_diffuse(struct world* world, Entity entity);
RenderTexturedUnlit* mix_render_textured_unlit(struct world* world, Entity entity);
