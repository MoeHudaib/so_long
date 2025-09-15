#include "map.h"

t_map   map_constructor(char *filename, char delimeter)
{
    t_map   map;
    int checker;
    
    checker = get_map_hw(filename, &map);
        if (checker < 0)
            exit(1);
    checker = set_map_grid(filename, &map, delimeter);
        if (checker < 0)
        {
            free_tokens(map.grid);
            exit(1);
        }
    checker = map_validator(&map);
        if (checker < 0)
        {
            free_tokens(map.grid);
            exit(1);
        }
    checker = walls_checker(&map);
        if (checker < 0)
        {
            free_tokens(map.grid);
            exit(1);
        }
    return (map);
}

void    map_destructor(t_map *map)
{
    free_tokens(map->grid);
}