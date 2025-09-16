#include "map.h"
#include "get_next_line.h"
#include "libft/libft.h"

char *remove_nl(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (NULL);
    while (line[i])
    {
        if ( line[i] == '\n')
            line[i] = '\0';
        i++;
    }
    return (line);
}

int set_map_grid(const char *filename, t_map *map)
{
    char *line;
    int fd;
    int i;

    if (!filename)
        return (INVALID_FILE_NAME);

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (INVALID_FILE);

    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        return (INVALID_LINE);
    }

    map->grid = malloc(sizeof(char *) * (map->height + 1));
    if (!map->grid)
    {
        free(line);
        close(fd);
        return (MEMORY_ALLOCATION_FAILURE);
    }

    i = 0;
    while (line && i < map->height)
    {
        line = remove_nl(line);
        map->grid[i] = ft_strdup(line);
        if (!map->grid[i])
        {
            free_tokens(map->grid);
            free(line);
            close(fd);
            return (MEMORY_ALLOCATION_FAILURE);
        }
        i++;
        free(line);
        line = get_next_line(fd);
    }
    map->grid[i] = NULL;

    close(fd);
    return (0);
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

