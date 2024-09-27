#include "raycaster.h"

/**
 * draw_ceiling - Draw the ceiling
 * @renderer: SDL renderer
 */
void draw_ceiling(SDL_Renderer *renderer)
{
	SDL_Rect ceiling = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

	SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);  /* Light blue */
	SDL_RenderFillRect(renderer, &ceiling);
}

/**
 * draw_floor - Draw the floor
 * @renderer: SDL renderer
 */
void draw_floor(SDL_Renderer *renderer)
{
	SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);  /* Gray */
	SDL_RenderFillRect(renderer, &floor);
}

/**
 * cast_rays - Cast rays and render walls
 * @renderer: SDL renderer
 * @game: Pointer to the game structure
 */
void cast_rays(SDL_Renderer *renderer, game_t *game)
{
	double ray_angle, ray_x, ray_y, x_step, y_step, distance;
	int map_x, map_y, wall_height, i;
	double fov = M_PI / 3;  /* 60 degrees field of view */
	int num_rays = SCREEN_WIDTH;

	for (i = 0; i < num_rays; i++)
	{
		ray_angle = game->player.angle - fov / 2 + fov * i / num_rays;
		ray_x = game->player.x;
		ray_y = game->player.y;
		x_step = cos(ray_angle);
		y_step = sin(ray_angle);

		while (1)
		{
			map_x = (int)(ray_x / TILE_SIZE);
			map_y = (int)(ray_y / TILE_SIZE);

			if (is_wall(game->map, map_x, map_y))
			{
				distance = sqrt(pow(ray_x - game->player.x + ray_y - game->player.y, 2));
				distance *= cos(ray_angle - game->player.angle);  /* Fix fisheye effect */
				wall_height = (int)(SCREEN_HEIGHT / distance);

				SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  /* Light gray */
				SDL_RenderDrawLine(renderer, i, SCREEN_HEIGHT / 2 - wall_height / 2,
						   i, SCREEN_HEIGHT / 2 + wall_height / 2);
				break;
			}

			ray_x += x_step;
			ray_y += y_step;
		}
	}
}

/**
 * render_frame - Render a single frame of the game
 * @renderer: SDL renderer
 * @game: Pointer to the game structure
 */
void render_frame(SDL_Renderer *renderer, game_t *game)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_ceiling(renderer);
	draw_floor(renderer);
	cast_rays(renderer, game);

	/* Optionally draw 2D map for debugging */
	/* draw_map_2d(renderer, game->map); */

	SDL_RenderPresent(renderer);
}

