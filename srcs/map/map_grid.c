/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:23:00 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 19:41:42 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "get_next_line.h"
#include "libft/libft.h"

char	*remove_nl(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	return (line);
}

static char	**set_grid(t_map *map, int fd, char *line)
{
	char	**grid;

	grid = malloc(sizeof(char *) * (map->height + 1));
	if (!grid)
	{
		free(line);
		close(fd);
		return (NULL);
	}
	return (grid);
}

static int	fill_grid(t_map *map, int fd, char *line)
{
	int	i;

	i = 0;
	if (!line)
	{
		close(fd);
		return (INVALID_LINE);
	}
	while (line)
	{
		line = remove_nl(line);
		map->grid[i] = ft_strdup(line);
		if (!map->grid[i])
		{
			free(line);
			free_tokens(map->grid);
			close(fd);
			return (MEMORY_ALLOCATION_FAILURE);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	return (0);
}

int	set_map_grid(const char *filename, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (INVALID_FILE);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (INVALID_LINE);
	}
	map->grid = set_grid(map, fd, line);
	if (!map->grid)
		return (MEMORY_ALLOCATION_FAILURE);
	i = fill_grid(map, fd, line);
	if (i < 0)
		return (i);
	close(fd);
	return (0);
}
