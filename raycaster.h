#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define TILE_SIZE 64

/**
 * struct player_s - Structure to hold player data
 * @x: Player's x-coordinate
 * @y: Player's y-coordinate
 * @angle: Player's viewing angle
 */
typedef struct player_s
{
double x;
double y;
double angle;
} player_t;

/**
 * struct game_s - Structure to hold game data
 * @map: 2D array representing the game map
 * @player: Player data
 */
typedef struct game_s
{
int map[MAP_HEIGHT][MAP_WIDTH];
player_t player;
} game_t;

/* Function prototypes */
void init_game(game_t *game);
void render_frame(SDL_Renderer *renderer, game_t *game);
int init_sdl(SDL_Window **window, SDL_Renderer **renderer);

/* SDL initialization */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer);

/* Game initialization */
void init_game(game_t *game);

/* Input handling */
void handle_input(game_t *game);

/* Map functions */
void init_map(int map[MAP_HEIGHT][MAP_WIDTH]);
int is_wall(int map[MAP_HEIGHT][MAP_WIDTH], int x, int y);
void draw_map_2d(SDL_Renderer *renderer, int map[MAP_HEIGHT][MAP_WIDTH]);

/* Player functions */
void init_player(player_t *player);
void move_player(player_t *player, int map[MAP_HEIGHT][MAP_WIDTH], double dx, double dy);
void rotate_player(player_t *player, double angle);

/* Rendering functions */
void render_frame(SDL_Renderer *renderer, game_t *game);
void draw_ceiling(SDL_Renderer *renderer);
void draw_floor(SDL_Renderer *renderer);
void cast_rays(SDL_Renderer *renderer, game_t *game);

#endif

