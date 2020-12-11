#include "../common/entity.h"
#include "../common/matrix.h"

#include "com_collide.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_shoot.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_player_target(struct world* world, entity* target)
{
	// Primary rig controllable in the XZ plane.
	entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);
	root_transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};

	Move* root_move = mix_move(world, root);
	root_move->movement_speed = 10.0f;
	root_move->rotation_speed = 2.0f;

	ControlPlayer* root_control = mix_control_player(world, root);
	root_control->move = true;
	root_control->yaw = 0.1f;
	root_control->pitch = 0.0f;

	Collide* collide = mix_collide(world, root);
	collide->dynamic = true;
	collide->layers = LAYER_PLAYER;
	collide->mask = LAYER_TERRAIN;

	{
		// Secondary rig which can pitch up and down.
		entity rig = create_entity(world);
		root_transform->children[0] = rig;

		// The secondary rig is the target of the follow camera.
		*target = rig;

		Transform* rig_transform = mix_transform(world, rig);
		rig_transform->parent = root;

		Move* rig_move = mix_move(world, rig);
		rig_move->movement_speed = 0.0f;
		rig_move->rotation_speed = 2.0f;

		ControlPlayer* rig_control = mix_control_player(world, rig);
		rig_control->move = false;
		rig_control->yaw = 0.0f;
		rig_control->pitch = 0.1f;
		rig_control->shoot = true;

		Shoot* rig_shoot = mix_shoot(world, rig);
		rig_shoot->frequency = 0.2f;
		rig_shoot->since_last = 0.2f;
	}

	return root;
}
