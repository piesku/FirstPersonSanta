#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "world.h"

entity blueprint_sofa(struct world* world, vec3 translation, quat rotation)
{
	entity sofa = create_entity(world);

	Transform* transform = mix_transform(world, sofa);
	transform->translation = translation;
	transform->rotation = rotation;

	Collide* collide = mix_collide(world, sofa);
	collide->dynamic = false;
	collide->layers = LAYER_NONE;
	collide->mask = LAYER_PLAYER;
	collide->aabb.size = (vec3){1.0f, 3.0f, 1.0f};

	{
		entity mesh = create_entity(world);
		transform->children[0] = mesh;

		Transform* mesh_transform = mix_transform(world, mesh);
		mesh_transform->parent = sofa;

		RenderColoredUnlit* mesh_render = mix_render_colored_unlit(world, mesh);
		mesh_render->material = MAT_COLORED_UNLIT;
		mesh_render->mesh = MESH_SOFA;
		mesh_render->color = (vec4){0.32f, 0.4f, 0.88f, 1.0f};
	}

	return sofa;
}
