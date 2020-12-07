#include "../common/entity.h"
#include "../common/matrix.h"

#include "com_camera.h"
#include "com_control_player.h"
#include "com_mimic.h"
#include "com_move.h"
#include "com_shoot.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

entity blueprint_camera_display(struct world* world)
{
	// Primary camera rig controllable by the player in the XZ plane.
	entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);
	root_transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};

	Move* root_move = mix_move(world, root);
	root_move->movement_speed = 20.0f;
	root_move->rotation_speed = 2.0f;

	ControlPlayer* root_control = mix_control_player(world, root);
	root_control->move = true;
	root_control->yaw = 0.1f;
	root_control->pitch = 0.0f;

	{
		// Secondary camera rig which can pitch up and down.
		entity rig = create_entity(world);
		root_transform->children[0] = rig;

		Transform* rig_transform = mix_transform(world, rig);
		rig_transform->parent = root;

		Move* rig_move = mix_move(world, rig);
		rig_move->movement_speed = 0.0f;
		rig_move->rotation_speed = 2.0f;

		ControlPlayer* rig_control = mix_control_player(world, rig);
		rig_control->move = false;
		rig_control->yaw = 0.0f;
		rig_control->pitch = 0.1f;

		{
			// Actual camera entity, rotated 180y to align with the rig's forward.
			entity camera = create_entity(world);
			rig_transform->children[0] = camera;

			Transform* camera_transform = mix_transform(world, camera);
			camera_transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};
			camera_transform->parent = rig;

			CameraDisplay* camera_display = mix_camera_display(world, camera);
			camera_display->fov_y = 1.0f;
			camera_display->near = 0.5f;
			camera_display->far = 1000.0f;
			camera_display->clear_color = (vec4){0.9f, 0.9f, 0.9f, 1.0f};
		}
	}

	return root;
}

entity blueprint_camera_player(struct world* world)
{
	// Primary camera rig controllable by the player in the XZ plane.
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

	{
		// Secondary camera rig which can pitch up and down.
		entity rig = create_entity(world);
		root_transform->children[0] = rig;

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

		{
			// Actual camera entity, rotated 180y to align with the rig's forward.
			entity camera = create_entity(world);
			rig_transform->children[0] = camera;

			Transform* camera_transform = mix_transform(world, camera);
			camera_transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};
			camera_transform->parent = rig;

			CameraFramebuffer* camera_framebuffer = mix_camera_framebuffer(world, camera);
			camera_framebuffer->fov_y = 1.0f;
			camera_framebuffer->near = 0.5f;
			camera_framebuffer->far = 1000.0f;
			camera_framebuffer->clear_color = (vec4){0.9f, 0.9f, 0.9f, 1.0f};
			camera_framebuffer->target = RENDER_TARGET_DEFAULT;
		}
	}

	return root;
}

entity blueprint_camera_follow(struct world* world)
{
	entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);
	root_transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};

	mix_mimic(world, root);

	{
		// Actual camera entity, rotated 180y to align with the rig's forward.
		entity child = create_entity(world);
		root_transform->children[0] = child;

		Transform* child_transform = mix_transform(world, child);
		child_transform->rotation = (quat){0.0f, 1.0f, 0.0f, 0.0f};
		child_transform->parent = root;

		CameraFramebuffer* camera = mix_camera_framebuffer(world, child);
		camera->fov_y = 1.0f;
		camera->near = 0.5f;
		camera->far = 1000.0f;
		camera->clear_color = (vec4){0.9f, 0.9f, 0.9f, 1.0f};
		camera->target = RENDER_TARGET_DEFAULT;
	}

	return root;
}

entity blueprint_camera_minimap(struct world* world)
{
	// Camera rig.
	entity root = create_entity(world);

	Transform* root_transform = mix_transform(world, root);
	quat_from_euler(&root_transform->rotation, 90, 180, 0);

	{
		// Actual camera entity, rotated 180y to align with the rig's forward.
		entity camera = create_entity(world);
		root_transform->children[0] = camera;

		Transform* camera_transform = mix_transform(world, camera);
		camera_transform->rotation = (quat){0.0, 1.0, 0.0, 0.0};
		camera_transform->parent = root;

		CameraFramebuffer* camera_framebuffer = mix_camera_framebuffer(world, camera);
		camera_framebuffer->fov_y = 1.0;
		camera_framebuffer->near = 1.0;
		camera_framebuffer->far = 1000.0;
		camera_framebuffer->clear_color = (vec4){1.0f, 1.0f, 1.0f, 1.0f};
		camera_framebuffer->target = RENDER_TARGET_MINIMAP;
	}

	return root;
}
