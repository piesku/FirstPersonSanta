#include "blu_camera.h"

#include "com_camera.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_transform.h"
#include "world.h"

entity blueprint_camera(struct world* world)
{
	// Camera rig controllable by the player.
	entity a = create_entity(world);

	Transform* transform_a = mix_transform(world, a);
	transform_a->translation[0] = 0.0;
	transform_a->translation[1] = 0.0;
	transform_a->translation[2] = 2.0;
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
	control->pitch = 0.1;

	{
		// Actual camera entity, rotated 180y to align with the rig's forward.
		entity b = create_entity(world);

		Transform* transform_b = mix_transform(world, b);
		transform_b->rotation[0] = 0.0;
		transform_b->rotation[1] = 1.0;
		transform_b->rotation[2] = 0.0;
		transform_b->rotation[3] = 0.0;

		Camera* camera = mix_camera(world, b);
		camera->fov_y = 1.0;
		camera->near = 0.1;
		camera->far = 1000.0;

		transform_a->children[0] = b;
		transform_b->parent = a;
	}

	return a;
}
