#include "raycaster.h"

/**
 * init_player - Initialize the player's position and angle
 * @player: Pointer to the player structure
 */
void init_player(player_t *player)
{
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->angle = 0;
}

/**
 * move_player - Move the player based on input
 * @player: Pointer to the player structure
 * @map: 2D array representing the game map
 * @dx: Change in x direction
 * @dy: Change in y direction
 */
void move_player(player_t *player, int map[MAP_HEIGHT][MAP_WIDTH], double dx, double dy)
{
	double new_x = player->x + dx;
	double new_y = player->y + dy;

	/* Check for collision with walls */
	if (!is_wall(map, (int)(new_x / TILE_SIZE), (int)(new_y / TILE_SIZE)))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

/**
 * rotate_player - Rotate the player
 * @player: Pointer to the player structure
 * @angle: Angle to rotate by (in radians)
 */
void rotate_player(player_t *player, double angle)
{
	player->angle += angle;
	/* Keep angle between 0 and 2*PI */
	player->angle = fmod(player->angle, 2 * M_PI);
	if (player->angle < 0)
		player->angle += 2 * M_PI;
}

