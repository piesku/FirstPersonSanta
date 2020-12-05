#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "common/gl.h"
#include "common/texture.h"
#include "game/client.h"
#include "game/world.h"

void scene_collide(struct world* world);
void scene_cube(struct world* world);
void scene_main(struct world* world);
void scene_minimap(struct world* world);
void scene_monkey(struct world* world);
void scene_physics(struct world* world);

struct engine {
	clock_t last_time;
	SDL_Window* window;
	SDL_GLContext context;

	int viewport_width;
	int viewport_height;

	struct client client;
	struct world* world;
};

void engine_load_texture(struct engine* engine, enum texture_index index, const char* filename)
{
	SDL_Surface* image = IMG_Load(filename);
	if (image == NULL) {
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(1);
	}
	engine->client.textures[index] = create_texture_from(
			image->pixels, image->w, image->h);
	SDL_FreeSurface(image);
}

void engine_init_display(struct engine* engine)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Window options.
	SDL_SetRelativeMouseMode(true);

	// OpenGL window attribute set before window creation.
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	engine->viewport_width = 960;
	engine->viewport_height = 600;
	engine->window = SDL_CreateWindow("FirstPerson",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			engine->viewport_width, engine->viewport_height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (engine->window == NULL) {
		printf("Failed to create window: %s\n", SDL_GetError());
		exit(1);
	}

	engine->context = SDL_GL_CreateContext(engine->window);
	if (engine->context == NULL) {
		printf("Failed to create context: %s\n", SDL_GetError());
		exit(1);
	}

	// Context options which require a current GL context.
	SDL_GL_SetSwapInterval(1);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK) {
		printf("Failed to init GLEW: %s\n", glewGetErrorString(glew_error));
		exit(1);
	}
#endif

	int img_requested = IMG_INIT_PNG;
	int img_supported = IMG_Init(img_requested);
	if ((img_supported & img_requested) != img_requested) {
		printf("Failed to init SDL2_image: %s\n", IMG_GetError());
		exit(1);
	}

	engine_load_texture(engine, TEX_CHECKER, "textures/checker1.png");
	client_setup(&engine->client, engine->viewport_width, engine->viewport_height);
}

void engine_term_display(struct engine* engine)
{
	client_teardown(&engine->client);

	IMG_Quit();
	SDL_GL_DeleteContext(engine->context);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	struct engine engine = (struct engine){
			.world = create_world(),
			.last_time = clock() - 1,
	};

	engine_init_display(&engine);
	scene_monkey(engine.world);

	bool quit = false;
	while (quit == false) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.repeat)
						break;
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_ESCAPE:
							quit = true;
							break;
						case SDL_SCANCODE_UP:
							engine.client.input_state.arrow_up = 1;
							engine.client.input_delta.arrow_up = 1;
							break;
						case SDL_SCANCODE_DOWN:
							engine.client.input_state.arrow_down = 1;
							engine.client.input_delta.arrow_down = 1;
							break;
						case SDL_SCANCODE_LEFT:
							engine.client.input_state.arrow_left = 1;
							engine.client.input_delta.arrow_left = 1;
							break;
						case SDL_SCANCODE_RIGHT:
							engine.client.input_state.arrow_right = 1;
							engine.client.input_delta.arrow_right = 1;
							break;
						case SDL_SCANCODE_W:
							engine.client.input_state.key_w = 1;
							engine.client.input_delta.key_w = 1;
							break;
						case SDL_SCANCODE_S:
							engine.client.input_state.key_s = 1;
							engine.client.input_delta.key_s = 1;
							break;
						case SDL_SCANCODE_A:
							engine.client.input_state.key_a = 1;
							engine.client.input_delta.key_a = 1;
							break;
						case SDL_SCANCODE_D:
							engine.client.input_state.key_d = 1;
							engine.client.input_delta.key_d = 1;
							break;
					}
					break;
				case SDL_KEYUP:
					if (event.key.repeat)
						break;
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_UP:
							engine.client.input_state.arrow_up = 0;
							engine.client.input_delta.arrow_up = -1;
							break;
						case SDL_SCANCODE_DOWN:
							engine.client.input_state.arrow_down = 0;
							engine.client.input_delta.arrow_down = -1;
							break;
						case SDL_SCANCODE_LEFT:
							engine.client.input_state.arrow_left = 0;
							engine.client.input_delta.arrow_left = -1;
							break;
						case SDL_SCANCODE_RIGHT:
							engine.client.input_state.arrow_right = 0;
							engine.client.input_delta.arrow_right = -1;
							break;
						case SDL_SCANCODE_W:
							engine.client.input_state.key_w = 0;
							engine.client.input_delta.key_w = -1;
							break;
						case SDL_SCANCODE_S:
							engine.client.input_state.key_s = 0;
							engine.client.input_delta.key_s = -1;
							break;
						case SDL_SCANCODE_A:
							engine.client.input_state.key_a = 0;
							engine.client.input_delta.key_a = -1;
							break;
						case SDL_SCANCODE_D:
							engine.client.input_state.key_d = 0;
							engine.client.input_delta.key_d = -1;
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					engine.client.input_state.mouse_x = event.motion.x;
					engine.client.input_state.mouse_y = event.motion.y;
					engine.client.input_delta.mouse_x = event.motion.xrel;
					engine.client.input_delta.mouse_y = event.motion.yrel;
				default:
					break;
			}
		}

		clock_t current_time = clock();
		clock_t delta = current_time - engine.last_time;

		float delta_s = (float)delta / CLOCKS_PER_SEC;
		engine.client.delta = delta_s;

		char fps[32];
		snprintf(fps, 32, "Frame: %4.3fs (%2.0f fps)", delta_s, 1.0f / delta_s);
		SDL_SetWindowTitle(engine.window, fps);

		client_world_update(&engine.client, engine.world, delta_s);
		client_input_reset(&engine.client);

		client_frame_update(&engine.client, engine.world);
		SDL_GL_SwapWindow(engine.window);

		engine.last_time = current_time;
	}

	engine_term_display(&engine);
	return 0;
}
