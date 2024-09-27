#include "raycaster.h"

/**
 * init_game - Initialize the game state
 * @game: Pointer to the game structure
 */
void init_game(game_t *game)
{
	int x, y;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
				game->map[y][x] = 1;
			else
				game->map[y][x] = 0;
		}
	}

	game->player.x = SCREEN_WIDTH / 2;
	game->player.y = SCREEN_HEIGHT / 2;
	game->player.angle = 0;
}

/**
 * cast_ray - Cast a single ray and draw the result
 * @renderer: SDL renderer
 * @game: Pointer to the game structure
 * @ray_angle: Angle of the ray being cast
 */
void cast_ray(SDL_Renderer *renderer, game_t *game, double ray_angle)
{
	double ray_x = game->player.x;
	double ray_y = game->player.y;
	double step_size = 1;
	double x_step = step_size * cos(ray_angle);
	double y_step = step_size * sin(ray_angle);
	int map_x, map_y;

	while (1)
	{
		map_x = (int)(ray_x / TILE_SIZE);
		map_y = (int)(ray_y / TILE_SIZE);

		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
			break;

		if (game->map[map_y][map_x] == 1)
		{
			double distance = sqrt(pow(ray_x - game->player.x, 2) +
					       pow(ray_y - game->player.y, 2));
			int wall_height = (int)(SCREEN_HEIGHT /
						(distance * cos(ray_angle - game->player.angle)));

			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderDrawLine(renderer, (int)ray_x, (int)ray_y,
					   (int)ray_x, (int)ray_y - wall_height / 2);
			SDL_RenderDrawLine(renderer, (int)ray_x, (int)ray_y,
					   (int)ray_x, (int)ray_y + wall_height / 2);
			break;
		}

		ray_x += x_step;
		ray_y += y_step;
	}
}
