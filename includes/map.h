#ifndef MAP_H
#define MAP_H
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "./libft/libft.h"
#include <fcntl.h>

typedef enum e_error_type
{
    INVALID_FILE = -42,
    INVALID_XPM_FILE,
    INVALID_WIDTH,
    INVALID_FILE_NAME,
    INVLAID_GRID,
    INVALID_HEIGHT,
    INVALID_LINE_LENGTH,
    INVALID_CHARACTER,
    INVALID_LINE,
    MULTIPLE_PLAYERS,
    NO_PLAYER,
    NO_EXIT,
    NO_COLLECTIBLE,
    MEMORY_ALLOCATION_FAILURE
}   t_error_type;

typedef struct s_map
{
    char    **grid; // nul-terminated rows
    int     width;  // DONE
    int     height; // DONE
    int     collectibles;
    int     player_count;
    int     exit_count;
    t_player   player;
    t_enemy    *enemies;
    t_point     sb_posistion; // Status Bar
    int        enemy_count;
}   t_map;

// Function prototypes
// load map from file
// validate map
// free map resources
// render map
// update map state
void free_tokens(char **tokens);
int get_map_hw(const char *filename, t_map *map);
int set_map_grid(const char *filename, t_map *map, char map_delimeter);
void free_grid(char **grid, int count);
int walls_checker(t_map *map);
int map_validator(t_map *map);
t_map   map_constructor(char *filename, char delimeter);
void    map_destructor(t_map *map);

#endif
