#include "raycaster.h"

/**
 * init_sdl - Initialize SDL and create window and renderer
 * @window: Pointer to SDL_Window pointer
 * @renderer: Pointer to SDL_Renderer pointer
 *
 * Return: 0 on success, 1 on failure
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL init failed! Error: %s\n", SDL_GetError());
		return (1);
	}

	*window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (*window == NULL)
	{
		fprintf(stderr, "Window creation failed! Error: %s\n", SDL_GetError());
		return (1);
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
		fprintf(stderr, "Renderer creation failed! Error: %s\n", SDL_GetError());
		return (1);
	}

	return (0);
}

/**
 * handle_input - Process keyboard input for player movement
 * @game: Pointer to the game structure
 */
void handle_input(game_t *game)
{
const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
double move_speed = 5.0;
double rotate_speed = 0.1;

if (keyboard_state[SDL_SCANCODE_W])
{
move_player(&game->player, game->map,
cos(game->player.angle) * move_speed,
sin(game->player.angle) * move_speed);
}
if (keyboard_state[SDL_SCANCODE_S])
{
move_player(&game->player, game->map,
-cos(game->player.angle) * move_speed,
-sin(game->player.angle) * move_speed);
}
if (keyboard_state[SDL_SCANCODE_A])
rotate_player(&game->player, -rotate_speed);
if (keyboard_state[SDL_SCANCODE_D])
rotate_player(&game->player, rotate_speed);
}

/**
 * main - Entry point for the raycaster program
 * @argc: Number of command-line arguments (unused)
 * @argv: Array of command-line argument strings (unused)
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
game_t game;
SDL_Event e;
int quit = 0;

if (init_sdl(&window, &renderer) != 0)
return (1);

init_game(&game);

while (!quit)
{
while (SDL_PollEvent(&e) != 0)
{
if (e.type == SDL_QUIT)
quit = 1;
}

handle_input(&game);
render_frame(renderer, &game);
}

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();

return (0);
}
