#pragma once
#include "../common/entity.h"
#include "../common/matrix.h"
#include "../common/material.h"
#include "../common/mesh.h"
#include "../common/texture.h"

#include "index.h"

enum render_kind {
	RENDER_BASIC_COLORED,
	RENDER_BASIC_TEXTURED,
	RENDER_DIFFUSE,
};

typedef struct render_basic_colored {
	enum material_index material;
	enum mesh_index mesh;
	vec4 color;
} RenderBasicColored;

typedef struct render_basic_textured {
	enum material_index material;
	enum mesh_index mesh;
	enum asset_index texture;
} RenderBasicTextured;

typedef struct render_diffuse {
	enum material_index material;
	enum mesh_index mesh;
	vec4 color;
} RenderDiffuse;

typedef struct render {
	enum render_kind kind;
	union {
		RenderBasicColored basic_colored;
		RenderBasicTextured basic_textured;
		RenderDiffuse diffuse;
	} value;
} Render;

struct world;
RenderBasicColored* mix_render_basic_colored(struct world* world, entity entity);
RenderBasicTextured* mix_render_basic_textured(struct world* world, entity entity);
RenderDiffuse* mix_render_diffuse(struct world* world, entity entity);
