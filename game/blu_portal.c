#include "../common/entity.h"
#include "../common/matrix.h"

#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "com_trigger.h"
#include "index.h"
#include "world.h"

Entity blueprint_portal(struct world* world)
{
	Entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);

	RenderColoredUnlit* root_render = mix_render_colored_unlit(world, root);
	root_render->material = MAT_COLORED_UNLIT;
	root_render->mesh = MESH_FIREPLACE;
	root_render->color = (vec4){0.3f, 0.4f, 0.9f, 1.0f};

	{
		Entity entry = create_entity(world);
		entity_list_push(&root_transform->children, entry);

		Transform* entry_transform = mix_transform(world, entry);
		entry_transform->translation = (vec3){0, 0.5f, -0.1f};
		entry_transform->scale = (vec3){0.2f, 0.2f, 0.01f};
		entry_transform->parent = root;

		//RenderColoredUnlit* entry_render = mix_render_colored_unlit(world, entry);
		//entry_render->material = MAT_COLORED_UNLIT;
		//entry_render->mesh = MESH_CUBE;
		//entry_render->color = (vec4){1, 0, 1, 1};

		Collide* entry_collide = mix_collide(world, entry);
		entry_collide->dynamic = false;
		entry_collide->layers = LAYER_NONE;
		entry_collide->mask = LAYER_PLAYER;

		Trigger* entry_trigger = mix_trigger(world, entry);
		entry_trigger->action = ACTION_TRIGGER_PORTAL;
		entry_trigger->mask = LAYER_PLAYER;
	}

	{
		Entity exit = create_entity(world);
		entity_list_push(&root_transform->children, exit);

		Transform* exit_transform = mix_transform(world, exit);
		exit_transform->translation = (vec3){0, 0, -250};
		exit_transform->rotation = (quat){0, 1, 0, 0};
		exit_transform->scale = (vec3){10, 10, 10};
		exit_transform->parent = root;

		//RenderColoredUnlit* exit_render = mix_render_colored_unlit(world, exit);
		//exit_render->material = MAT_COLORED_UNLIT;
		//exit_render->mesh = MESH_CUBE;
		//exit_render->color = (vec4){1, 0, 1, 1};

		Collide* exit_collide = mix_collide(world, exit);
		exit_collide->dynamic = false;
		exit_collide->layers = LAYER_NONE;
		exit_collide->mask = LAYER_CAMERA;

		Trigger* exit_trigger = mix_trigger(world, exit);
		exit_trigger->action = ACTION_TRIGGER_EXIT;
		exit_trigger->mask = LAYER_CAMERA;
	}

	return root;
}
