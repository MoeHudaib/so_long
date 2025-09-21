/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:30:12 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/09/21 16:15:41 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_tokens_i(char **grid, int i)
{
	if (!grid || !i)
	{
		return ;
	}
	while (i >= 0)
	{
		free(grid[i]);
		i--;
	}
	free(grid);
}

int	free_visit(int **visited, int i, t_map *map)
{
	int	x;

	if (!visited)
		return (INVLAID_GRID);
	x = 0;
	if (i > 0)
	{
		while (x < i)
		{
			free(visited[x]);
			x++;
		}
	}
	free(visited);
	map_destructor(map);
	return (MEMORY_ALLOCATION_FAILURE);
}

void	walk_through_exit(int new_x, int new_y, t_minilibx *data)
{
	int	x;
	int	y;

	if (data->map.grid[new_y][new_x] == 'E')
	{
		if (data->map.collectibles == 0)
			game_over(data, 1);
		data->map.exit_pose.x = new_x;
		data->map.exit_pose.y = new_y;
	}
	x = data->map.exit_pose.x;
	y = data->map.exit_pose.y;
	if (new_x == x && new_y == y)
	{
		if (data->map.collectibles == 0)
			game_over(data, 1);
	}
}
