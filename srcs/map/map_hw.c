/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_hw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:40:33 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/09/20 19:35:03 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_strlen_no_nl(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len] && str[len] != '\n')
		len++;
	return (len);
}

static int	get_width(const char *line)
{
	int	len;

	if (!line)
		return (-1);
	len = ft_strlen_no_nl(line);
	if (len <= 0)
		return (-1);
	return (len);
}

static int	read_hw(int fd, t_map *map)
{
	int		height;
	char	*line;

	height = 0;
	line = get_next_line(fd);
	map->width = get_width(line);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
		if (line && (int)ft_strlen_no_nl(line) != map->width)
		{
			free(line);
			return (INVALID_WIDTH);
		}
	}
	free(line);
	map->height = height;
	if (height <= 0)
		return (INVALID_HEIGHT);
	return (0);
}

int	get_map_hw(const char *filename, t_map *map)
{
	int	fd;
	int	status;

	if (!filename || !map)
		return (INVALID_FILE_NAME);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (INVALID_FILE);
	status = read_hw(fd, map);
	if (map->height >= 30 || map->width >= 60)
		return (INVALID_WIDTH);
	if (map->height == map->width)
		return (INVALID_WIDTH);
	close(fd);
	map->exit_count = 0;
	return (status);
}
