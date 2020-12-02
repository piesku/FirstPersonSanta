#pragma once

enum framebuffer_index {
	FB_NONE,
	FB_RENDER_TO_TEXTURE,
	FRAMEBUFERS_LENGTH,
};

enum texture_index {
	TEX_NONE,
	TEX_RENDER_RGBA,
	TEX_RENDER_DEPTH,
	TEX_CHECKER,
	TEXTURES_LENGTH,
};

enum material_index {
	MAT_COLORED_UNLIT,
	MAT_TEXTURED_UNLIT,
	MATERIALS_LENGTH,
};

enum mesh_index {
	MESH_CUBE,
	MESHES_LENGTH,
};
