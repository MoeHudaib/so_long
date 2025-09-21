/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:37:50 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/21 13:42:02 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_characters(t_map *map, int i, int j, int *p_flag)
{
	t_player	player;
	t_point		point;

	if (is_in_set(map->grid[i][j], "10ECPN") != 0)
		return (INVALID_CHARACTER);
	if (map->grid[i][j] == 'P' && !*p_flag)
	{
		point.x = j;
		point.y = i;
		player = init_player(point, 100);
		map->player = player;
		*p_flag = 1;
	}
	else if (map->grid[i][j] == 'P' && *p_flag)
		return (MULTIPLE_PLAYERS);
	else if (map->grid[i][j] == 'E')
		map->exit_count++;
	if (map->exit_count > 1)
		return (MUTLIPLE_EXITS);
	return (0);
}

int	map_validator(t_map *map)
{
	int	i;
	int	j;
	int	height;
	int	p_flag;

	i = -1;
	height = 0;
	p_flag = 0;
	while (map->grid[++i])
	{
		height++;
		if (ft_strlen_no_nl(map->grid[i]) != map->width)
			return (INVALID_WIDTH);
		j = -1;
		while (map->grid[i][++j])
			if ((check_characters(map, i, j, &p_flag)) < 0)
				return (check_characters(map, i, j, &p_flag));
	}
	if (map->height != height)
		return (INVALID_HEIGHT);
	if (!p_flag)
		return (NO_PLAYER);
	return (0);
}

static int	check_edges(t_map *map, int i, int j)
{
	if (i == 0 && map->grid[i][j] != '1')
		return (INVALID_CHARACTER);
	if (j == 0 && map->grid[i][j] != '1')
		return (INVALID_CHARACTER);
	if (i == map->height - 1 && map->grid[i][j] != '1')
		return (INVALID_CHARACTER);
	if (j == map->width - 1 && map->grid[i][j] != '1')
		return (INVALID_CHARACTER);
	return (0);
}

int	walls_checker(t_map *map)
{
	int	i;
	int	j;
	int	err;

	i = -1;
	err = 0;
	while (map->grid[++i])
	{
		j = -1;
		while (map->grid[i][++j])
			if ((check_edges(map, i, j)) != 0)
				err = INVALID_CHARACTER;
	}
	if (err != 0)
		map_destructor(map);
	return (err);
}
