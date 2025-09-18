#include <stdlib.h>
#include <stdio.h>
#include "map.h"

char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int ft_strlen1(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

char **copy_grid(char **grid)
{
    int i, rows;
    char **copy;

    if (!grid)
        return (NULL);
    rows = 0;
    while (grid[rows])
        rows++;

    copy = malloc(sizeof(char *) * (rows + 1));
    if (!copy)
        return (NULL);

    for (i = 0; i < rows; i++)
    {
        int len = ft_strlen1(grid[i]);
        copy[i] = malloc(len + 1);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        ft_strcpy(copy[i], grid[i]);
    }
    copy[rows] = NULL;
    return (copy);
}

/*
  DFS traversal:
- Explore all directions
- Mark visited[][]
- Detect exit + collectibles
*/
void dfs(int **visited, char **grid, int x, int y, int width, int height,
         int *exit_found, int *collectibles_found)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    if (visited[y][x])
        return;
    if (grid[y][x] == '1')
        return;

    visited[y][x] = 1;

    if (grid[y][x] == 'E')
        *exit_found = 1;
    if (grid[y][x] == 'C')
        (*collectibles_found)++;

    dfs(visited, grid, x + 1, y, width, height, exit_found, collectibles_found);
    dfs(visited, grid, x - 1, y, width, height, exit_found, collectibles_found);
    dfs(visited, grid, x, y + 1, width, height, exit_found, collectibles_found);
    dfs(visited, grid, x, y - 1, width, height, exit_found, collectibles_found);
}

int free_(t_map *map, int **visited, int exit_found, int clctbls_f)
{

    for (int i = 0; i < map->height; i++)
        free(visited[i]);
    free(visited);

    if (!exit_found)
        return (NO_EXIT);
    if (map->collectibles <= 0 || clctbls_f != map->collectibles)
        return (NO_COLLECTIBLE);
    return (0);
}

int set_vals(int *x1, int *x2, int *x3)
{
    *x1 = 0;
    *x2 = -1;
    *x3 = 0;
    return (0);
}

int check_solvable(t_map *map)
{
    int **visited;
    int exit_found;
    int i;
    int collectibles_found;

    set_vals(&exit_found, &i, &collectibles_found);
    visited = malloc(sizeof(int *) * map->height);
    if (!visited)
        return (MEMORY_ALLOCATION_FAILURE);
    while (++i < map->height)
    {
        visited[i] = calloc(map->width, sizeof(int));
        if (!visited[i])
            return (MEMORY_ALLOCATION_FAILURE);
    }
    dfs(visited, map->grid,
        map->player.position.x,
        map->player.position.y,
        map->width,
        map->height,
        &exit_found,
        &collectibles_found);
    return (free_(map, visited, exit_found, collectibles_found));
}

// int main()
// {
//     t_map map = map_constructor("srcs/map/hello.txt");
//     int c = check_solvable(&map);
//     printf("%d\n", c);
//     return (0);
// }
