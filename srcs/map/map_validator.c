#include "map.h"

void free_tokens(char **tokens)
{
    int i;

    if (!tokens)
        return;
    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

static int is_in_set(char c, char *set)
{
    int i;

    i = 0;
    while (set[i])
    {
        if (set[i] == c)
            return (0);
        i++;
    }
    return (INVALID_CHARACTER);
}

int map_validator(t_map *map)
{
    int i;
    int j;
    int height;
    int P_flag;
    size_t width;

    i = 0;
    height = 0;
    P_flag = 0;
    width = map->width;
    if (!map)
        return (INVLAID_GRID);
    while (map->grid[i])
    {
        height++;
        if (ft_strlen(map->grid[i]) != width)
            return (INVALID_WIDTH);
        else
        {
            j = 0;
            while (map->grid[i][j])
            {
                if (is_in_set(map->grid[i][j], "10ECPN") != 0)
                    return (INVALID_CHARACTER);
                if (map->grid[i][j] == 'P' && !P_flag)
                {
                    t_player player;
                    t_point point;
                    point.x = j;
                    point.y = i;
                    player = init_player(point, 100);
                    map->player = player;
                    P_flag = 1;
                }
                else if (map->grid[i][j] == 'P' && P_flag)
                    return (INVALID_CHARACTER);
                j++;
            }
        }
        i++;
    }
    if (!(map->height == height))
        return (INVALID_HEIGHT);
    return (0);
}

static int get_grid_size(t_map *map)
{
    int len;
    int j;
    int c;
    int n;

    len = 0;
    c = 0;
    n = 0;
    while(map->grid[len])
    {
        j = 0;
        while (map->grid[len][j])
        {
            if (map->grid[len][j] == 'C')
                c++;
            else if (map->grid[len][j] == 'N')
                n++;
            j++;
        }
        len++;
    }
    map->collectibles = c;
    map->enemy_count = n;
    return (len);
}

int walls_checker(t_map *map)
{
    int i;
    int j;

    get_grid_size(map);
    i = 0;
    while(map->grid[i])
    {
        j = 0;
        while(map->grid[i][j])
        {
            if (i == 0 && map->grid[i][j] != '1')
                return (INVALID_CHARACTER);
            if (j == 0 && map->grid[i][j] != '1')
                return (INVALID_CHARACTER);
            if (i == map->height - 1 && map->grid[i][j] != '1')
                return (INVALID_CHARACTER);
            if (j == map->width - 1 && map->grid[i][j] != '1')
                return (INVALID_CHARACTER);
            j++;
        }
        i++;
    }
    return (0);
}

// int main()
// {
//     t_map   map;
    
//     get_map_hw("hello.txt", &map);
//     set_map_grid("hello.txt", &map, ' ');
//     int i = 0;
//     int error = 0;
//     while (map.grid[i])
//     {
//         printf("%s\n", map.grid[i++]);
//     }
//     printf("Height: %d\nWidth: %d\n", map.height, map.width);
//     if ((error = map_validator(&map)) == 0)
//         printf("Your Map Is Valid\n");
//     else
//         printf("Your Map Is Invalid: %d\n", error);
//     if ((error = walls_checker(&map)) == 0)
//         printf("Your Map's Walls are CORRECT!\n");
//     else
//         printf("Your Map's Walls are INCORRECT!\n");
//     printf("ENEMIES COUNT: %d\nCOL COUNT: %d\n", map.enemy_count, map.collectible_count);
//     free_tokens(map.grid);
// }