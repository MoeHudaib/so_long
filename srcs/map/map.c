#include "map.h"

t_map   map_constructor(char *filename)
{
    t_map   map;
    int checker;
    
    checker = get_map_hw(filename, &map);
        if (checker < 0)
        {
            
            printf("issue is at get_hw");
            error_type(checker);
            map_destructor(&map);
            exit(1);
        }
    checker = set_map_grid(filename, &map);
        if (checker < 0)
        {
            printf("issue is at set_map");
            error_type(checker);
            map_destructor(&map);
            exit(1);
        }
    checker = map_validator(&map);
        if (checker < 0)
        {
            error_type(checker);
            exit(1);
        }
    get_grid_stats( &map);
    checker = walls_checker(&map);
        if (checker < 0)
         {
            printf("issue is at wall_checker");
            error_type(checker);
            map_destructor(&map);
            exit(1);
        }
    checker = check_solvable(&map);
        if (checker < 0)
        {
        error_type(checker);
        map_destructor(&map);
        exit(1);
        }
    return (map);
}

void    map_destructor(t_map *map)
{
    free_tokens(map->grid);
}

void    error_type(int error_type)
{
    if (error_type == INVALID_FILE)
        fprintf(stderr, "Error: Invalid file provided.\n");
    else if (error_type == INVALID_XPM_FILE)
        fprintf(stderr, "Error: Invalid XPM file.\n");
    else if (error_type == INVALID_WIDTH)
        fprintf(stderr, "Error: Invalid map width.\n");
    else if (error_type == INVALID_FILE_NAME)
        fprintf(stderr, "Error: Invalid file name.\n");
    else if (error_type == INVLAID_GRID)
        fprintf(stderr, "Error: Invalid grid format.\n");
    else if (error_type == INVALID_HEIGHT)
        fprintf(stderr, "Error: Invalid map height.\n");
    else if (error_type == INVALID_LINE_LENGTH)
        fprintf(stderr, "Error: Inconsistent line length in map.\n");
    else if (error_type == INVALID_CHARACTER)
        fprintf(stderr, "Error: Invalid character found in map.\n");
    else if (error_type == INVALID_LINE)
        fprintf(stderr, "Error: Invalid line in map.\n");
    else if (error_type == MULTIPLE_PLAYERS)
        fprintf(stderr, "Error: Multiple players defined in map.\n");
    else if (error_type == NO_PLAYER)
        fprintf(stderr, "Error: No player defined in map.\n");
    else if (error_type == NO_EXIT)
        fprintf(stderr, "Error: No exit defined in map.\n");
    else if (error_type == NO_COLLECTIBLE)
        fprintf(stderr, "Error: No collectible found in map.\n");
    else if (error_type == MEMORY_ALLOCATION_FAILURE)
        fprintf(stderr, "Error: Memory allocation failure.\n");
    else
        fprintf(stderr, "Error: Unknown error.\n");

    exit(EXIT_FAILURE); // quit program after reporting error
}