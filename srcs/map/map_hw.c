#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "map.h"
#include "get_next_line.h"
#include "libft/libft.h"

static int    get_width(char *line)
{
    char **tokens;
    int count;

    if (!line)
        return (INVALID_LINE);
    tokens = ft_split(line, ' ');
    if (!tokens)
        return (INVALID_LINE);
    count = 0;
    while (tokens[count])
        count++;
    free_tokens(tokens);
    return (count);
}

static int get_hw(int fd, t_map *map)
{
    int height;
    char *line;

    line = get_next_line(fd);
    if (!line)
        return (INVALID_LINE);
    height = 0;
    map->width = get_width(line);
    while (line)
    {
        height++;
        free(line);
        line = get_next_line(fd);
    }
    map->height = height;
    return (0);
}

int get_map_hw(const char *filename, t_map *map)
{
    int fd;

    if (!filename || !map)
        return (INVALID_FILE_NAME);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (INVALID_FILE);
    get_hw(fd, map);
    return (0); // Return 0 on success, -1 on failure
}
// #include <stdio.h>
// int main()
// {
//     t_map   map;
//     get_map_hw("hello.txt", &map);
//     printf("Height: %d\nWidth: %d\n", map.height, map.width);
// }