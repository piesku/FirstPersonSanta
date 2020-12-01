#include "blu_camera.h"

#include "com_camera.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

entity blueprint_camera(struct world* world)
{
	// Primary camera rig controllable by the player in the XZ plane.
	entity a = create_entity(world);

	Transform* transform_a = mix_transform(world, a);
	transform_a->translation.x = 0.0;
	transform_a->translation.y = 0.0;
	transform_a->translation.z = 2.0;
	transform_a->rotation[0] = 0.0;
	transform_a->rotation[1] = 1.0;
	transform_a->rotation[2] = 0.0;
	transform_a->rotation[3] = 0.0;

	Move* move = mix_move(world, a);
	move->movement_speed = 10.0;
	move->rotation_speed = 2.0;

	ControlPlayer* control = mix_control_player(world, a);
	control->move = true;
	control->yaw = 0.1;
	control->pitch = 0;

	{
		// Secondary camera rig which can pitch up and down.
		entity b = create_entity(world);

		Transform* transform_b = mix_transform(world, b);

		Move* move = mix_move(world, b);
		move->movement_speed = 0.0;
		move->rotation_speed = 2.0;

		ControlPlayer* control = mix_control_player(world, b);
		control->move = false;
		control->yaw = 0;
		control->pitch = 0.1;

		transform_a->children[0] = b;
		transform_b->parent = a;

		{
			// Actual camera entity, rotated 180y to align with the rig's forward.
			entity c = create_entity(world);

			Transform* transform_c = mix_transform(world, c);
			transform_c->rotation[0] = 0.0;
			transform_c->rotation[1] = 1.0;
			transform_c->rotation[2] = 0.0;
			transform_c->rotation[3] = 0.0;

			Camera* camera = mix_camera(world, c);
			camera->fov_y = 1.0;
			camera->near = 0.1;
			camera->far = 1000.0;

			transform_b->children[0] = c;
			transform_c->parent = b;
		}
	}

	return a;
}
