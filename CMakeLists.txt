cmake_minimum_required(VERSION 3.8)
project(FirstPerson)

add_executable(FirstPerson
	main.c

	common/malloc.c
	common/mat4.c
	common/material.c
	common/number.c
	common/quat.c
	common/texture.c
	common/vec3.c

	game/blu_camera.c
	game/client.c
	game/com_camera.c
	game/com_control_player.c
	game/com_light.c
	game/com_move.c
	game/com_render.c
	game/com_transform.c
	"game/mat_colored_unlit.c"
	game/mesh_cube.c
	game/sce_cube.c
	game/sce_main.c
	game/sys_camera.c
	game/sys_control_keyboard.c
	game/sys_light.c
	game/sys_move.c
	game/sys_render.c
	game/sys_transform.c
	game/world.c

	# TODO Build as a separate library.
	LodePNG/lodepng.c
)

if(MSVC)
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(SDL2 CONFIG REQUIRED)
	target_link_libraries(FirstPerson
		OpenGL::GL
		GLEW::GLEW
		SDL2::SDL2 SDL2::SDL2main
	)
elseif(APPLE)
	find_package(OpenGL REQUIRED)
	find_library(SDL2_LIBRARY SDL2 "/Library/Frameworks")
	find_library(SDL2_App PRIVATE ${SDL2_LIBRARY})
	target_include_directories(FirstPerson PRIVATE ${SDL2_INCLUDE_DIR})
	target_link_libraries(FirstPerson
		${OPENGL_LIBRARIES}
		${SDL2_LIBRARY}
	)
elseif(UNIX)
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(SDL2 CONFIG REQUIRED)
	target_link_libraries(FirstPerson
		m
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES}
		${SDL2_LIBRARIES}
	)
endif()
