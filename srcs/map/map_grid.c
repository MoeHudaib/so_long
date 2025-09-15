#include "map.h"
#include "get_next_line.h"
#include "libft/libft.h"

void free_grid(char **grid, int count)
{
    int i;
    
    if (!grid)
        return;
    
    i = 0;
    while (i < count)
    {
        free(grid[i]);
        grid[i] = NULL;
        i++;
    }
}

static char    *get_line_from_split(char **grid)
{
    char    *ptr;
    int i;

    if (!grid || !*grid)
        return (NULL);
    i = 0;
    while(grid[i])
        i++;
    ptr = malloc(i + 1);
    if (!ptr)
        return (NULL);
    i = 0;
    while (grid[i])
    {
        ptr[i] = grid[i][0];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}

static char    **get_map_grid(int fd, t_map *map, char c)
{
    char    **grid;
    char    **split;
    char    *line;
    char    *tmp;
    int     i;

    i = 0;
    grid = malloc(sizeof(char *) * (map->height + 1));
    if (!grid)
        return (NULL);
    line = get_next_line(fd);
    while (line && i < map->height)
    {
        split = ft_split(line, c);
        if (!split || !*split)
        {
            free(line);
            free_grid(grid, i); // Free previously allocated grid entries
            free(grid);
            return (NULL);
        }
        tmp = get_line_from_split(split);
        free_tokens(split); // Free split immediately after use
        split = NULL;
        if (!tmp || !*tmp)
        {
            free(line);
            free(tmp); // Free tmp if allocated but invalid
            free_grid(grid, i);
            free(grid);
            return (NULL);
        }
        grid[i] = ft_strdup(tmp);
        free(tmp); // Free tmp immediately after use
        tmp = NULL;
        if (!grid[i])
        {
            free(line);
            free_grid(grid, i);
            free(grid);
            return (NULL);
        }
        free(line);
        line = get_next_line(fd);
        i++;
    }
    if (i < map->height) // Handle case where we read less than actual lines
    {
        free(line);
        free_grid(grid, i);
        free(grid);
        return (NULL);
    }
    grid[i] = NULL;
    while (line)
    {
        free(line);
        line = get_next_line(fd);
    }
    return (grid);
}

int set_map_grid(const char *filename, t_map *map, char map_delimeter)
{
    int fd;

    if (!map || !filename)
        return (INVALID_FILE_NAME);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (INVALID_FILE);
    map->grid = get_map_grid(fd, map, map_delimeter);
    if (!map->grid)
        return (INVLAID_GRID);
    close(fd);
    return (0); // Return 0 on success
}
// #include <stdio.h>
// int main()
// {
//     t_map   map;
//     map.height = 8;
//     map.width = 9;
//     set_map_grid("hello.txt", &map, ' ');
//     int i = 0;
//     while (map.grid[i])
//     {
//         printf("%s\n", map.grid[i++]);
//     }
// }