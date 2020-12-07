cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake
	CACHE STRING "Vcpkg toolchain file")

project(FirstPerson)

add_executable(FirstPerson
	main.c

	common/aabb.c
	common/malloc.c
	common/mat4.c
	common/material.c
	common/number.c
	common/quat.c
	common/texture.c
	common/vec3.c

	game/actions.c
	game/blu_camera.c
	game/blu_gift.c
	game/client.c
	game/com_camera.c
	game/com_collide.c
	game/com_control_player.c
	game/com_light.c
	game/com_move.c
	game/com_render.c
	game/com_rigid_body.c
	game/com_shoot.c
	game/com_transform.c
	game/com_trigger.c
	game/mat_colored_unlit.c
	game/mat_postprocess.c
	game/mat_textured_unlit.c
	game/mesh_chair.c
	game/mesh_cube.c
	game/mesh_gift.c
	game/mesh_lamp.c
	game/mesh_monkey.c
	game/mesh_quad.c
	game/mesh_sofa.c
	game/sce_bounce.c
	game/sce_collide.c
	game/sce_cube.c
	game/sce_main.c
	game/sce_minimap.c
	game/sce_monkey.c
	game/sce_physics.c
	game/sce_room.c
	game/sys_camera.c
	game/sys_collide.c
	game/sys_control_keyboard.c
	game/sys_control_mouse.c
	game/sys_light.c
	game/sys_move.c
	game/sys_physics_integrate.c
	game/sys_physics_kinematic.c
	game/sys_physics_resolve.c
	game/sys_postprocess.c
	game/sys_render.c
	game/sys_shoot.c
	game/sys_transform.c
	game/sys_trigger.c
	game/world.c
)

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2-image CONFIG REQUIRED)
target_link_libraries(FirstPerson
	OpenGL::GL
	SDL2::SDL2
	SDL2::SDL2main
	SDL2::SDL2_image
)

if(MSVC)
	find_package(GLEW REQUIRED)
	target_link_libraries(FirstPerson
		GLEW::GLEW
	)
elseif(UNIX)
	find_package(GLEW REQUIRED)
	target_link_libraries(FirstPerson
		m
		GLEW::GLEW
		SDL2::SDL2-static
	)
endif()

# Copy assets
file(COPY textures DESTINATION ${CMAKE_BINARY_DIR})
