#include "raycaster.h"

/**
 * init_map - Initialize the game map
 * @map: 2D array representing the game map
 */
void init_map(int map[MAP_HEIGHT][MAP_WIDTH])
{
	int x, y;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
				map[y][x] = 1;  /* Wall */
			else
				map[y][x] = 0;  /* Empty space */
		}
	}

	/* Add some additional walls */
	map[2][2] = 1;
	map[2][3] = 1;
	map[3][2] = 1;
	map[4][4] = 1;
	map[4][5] = 1;
	map[5][4] = 1;
}

/**
 * is_wall - Check if a given position is a wall
 * @map: 2D array representing the game map
 * @x: X coordinate to check
 * @y: Y coordinate to check
 *
 * Return: 1 if the position is a wall, 0 otherwise
 */
int is_wall(int map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
return (1);  /* Out of bounds is considered a wall */

return (map[y][x] == 1);
}

/**
 * draw_map_2d - Draw a 2D representation of the map
 * @renderer: SDL renderer
 * @map: 2D array representing the game map
 */
void draw_map_2d(SDL_Renderer *renderer, int map[MAP_HEIGHT][MAP_WIDTH])
{
	int x, y;
	int cell_width = SCREEN_WIDTH / MAP_WIDTH;
	int cell_height = SCREEN_HEIGHT / MAP_HEIGHT;
	SDL_Rect rect;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			rect.x = x * cell_width;
			rect.y = y * cell_height;
			rect.w = cell_width;
			rect.h = cell_height;

			if (map[y][x] == 1)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

