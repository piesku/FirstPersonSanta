#include "blu_camera.h"

#include "../common/matrix.h"

#include "com_camera.h"
#include "com_control_player.h"
#include "com_move.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_display(struct world* world)
{
	// Primary camera rig controllable by the player in the XZ plane.
	entity a = create_entity(world);

	Transform* transform_a = mix_transform(world, a);
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
		transform_b->parent = a;
		transform_a->children[0] = b;

		Move* move = mix_move(world, b);
		move->movement_speed = 0.0;
		move->rotation_speed = 2.0;

		ControlPlayer* control = mix_control_player(world, b);
		control->move = false;
		control->yaw = 0;
		control->pitch = 0.1;

		{
			// Actual camera entity, rotated 180y to align with the rig's forward.
			entity c = create_entity(world);

			Transform* transform_c = mix_transform(world, c);
			transform_c->rotation[0] = 0.0;
			transform_c->rotation[1] = 1.0;
			transform_c->rotation[2] = 0.0;
			transform_c->rotation[3] = 0.0;
			transform_c->parent = b;
			transform_b->children[0] = c;

			CameraDisplay* camera = mix_camera_display(world, c);
			camera->fov_y = 1.0;
			camera->near = 0.1;
			camera->far = 1000.0;
			camera->clear_color[0] = 0.9f;
			camera->clear_color[1] = 0.9f;
			camera->clear_color[2] = 0.9f;
			camera->clear_color[3] = 1.0f;
		}
	}

	return a;
}

entity blueprint_camera_player(struct world* world)
{
	// Primary camera rig controllable by the player in the XZ plane.
	entity a = create_entity(world);

	Transform* transform_a = mix_transform(world, a);
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
		transform_b->parent = a;
		transform_a->children[0] = b;

		Move* move = mix_move(world, b);
		move->movement_speed = 0.0;
		move->rotation_speed = 2.0;

		ControlPlayer* control = mix_control_player(world, b);
		control->move = false;
		control->yaw = 0;
		control->pitch = 0.1;

		{
			// Actual camera entity, rotated 180y to align with the rig's forward.
			entity c = create_entity(world);

			Transform* transform_c = mix_transform(world, c);
			transform_c->rotation[0] = 0.0;
			transform_c->rotation[1] = 1.0;
			transform_c->rotation[2] = 0.0;
			transform_c->rotation[3] = 0.0;
			transform_c->parent = b;
			transform_b->children[0] = c;

			CameraFramebuffer* camera = mix_camera_framebuffer(world, c);
			camera->fov_y = 1.0;
			camera->near = 0.1;
			camera->far = 1000.0;
			camera->clear_color[0] = 0.9f;
			camera->clear_color[1] = 0.9f;
			camera->clear_color[2] = 0.9f;
			camera->clear_color[3] = 1.0f;
			camera->target = FB_RENDER;

			float aspect = 960.0f / 600.0f;
			mat4_perspective(camera->projection, camera->fov_y, aspect, camera->near, camera->far);
		}
	}

	return a;
}

entity blueprint_camera_minimap(struct world* world)
{
	// Camera rig.
	entity a = create_entity(world);

	Transform* transform_a = mix_transform(world, a);
	quat_from_euler(transform_a->rotation, 90, 180, 0);

	{
		// Actual camera entity, rotated 180y to align with the rig's forward.
		entity b = create_entity(world);

		Transform* transform_b = mix_transform(world, b);
		transform_b->rotation[0] = 0.0;
		transform_b->rotation[1] = 1.0;
		transform_b->rotation[2] = 0.0;
		transform_b->rotation[3] = 0.0;
		transform_b->parent = a;
		transform_a->children[0] = b;

		CameraFramebuffer* camera = mix_camera_framebuffer(world, b);
		camera->fov_y = 1.0;
		camera->near = 0.1;
		camera->far = 1000.0;
		camera->clear_color[0] = 1.0f;
		camera->clear_color[1] = 1.0f;
		camera->clear_color[2] = 1.0f;
		camera->clear_color[3] = 1.0f;
		camera->target = FB_MINIMAP;

		mat4_perspective(camera->projection, camera->fov_y, 1.0f, camera->near, camera->far);
	}

	return a;
}
