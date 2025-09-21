/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:37:19 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/21 12:20:46 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (INVALID_CHARACTER);
}

void	get_grid_stats(t_map *map)
{
	int	i;
	int	j;

	map->collectibles = 0;
	map->enemy_count = 0;
	map->exit_pose.x = 0;
	map->exit_pose.y = 0;
	i = -1;
	while (map->grid[++i])
	{
		j = -1;
		while (map->grid[i][++j])
		{
			if (map->grid[i][j] == 'C')
				map->collectibles++;
			else if (map->grid[i][j] == 'N')
				map->enemy_count++;
		}
	}
}
