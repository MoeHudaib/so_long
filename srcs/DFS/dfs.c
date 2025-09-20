/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:18:50 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 12:51:36 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	dfs(int **visited, t_map *map, t_point pos, t_state *st)
{
	if (pos.x < 0 || pos.x >= map->width || pos.y < 0 || pos.y >= map->height)
		return ;
	if (visited[pos.y][pos.x] || map->grid[pos.y][pos.x] == '1')
		return ;
	visited[pos.y][pos.x] = 1;
	if (map->grid[pos.y][pos.x] == 'E')
		st->exit_found = 1;
	if (map->grid[pos.y][pos.x] == 'C')
		st->collectibles_found++;
	dfs(visited, map, (t_point){pos.x + 1, pos.y}, st);
	dfs(visited, map, (t_point){pos.x - 1, pos.y}, st);
	dfs(visited, map, (t_point){pos.x, pos.y + 1}, st);
	dfs(visited, map, (t_point){pos.x, pos.y - 1}, st);
}

static void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

static int	validate_result(t_map *map, t_state st)
{
	if (!st.exit_found)
	{
		map_destructor(map);
		return (NO_EXIT);
	}
	if (map->collectibles <= 0 || st.collectibles_found != map->collectibles)
	{
		map_destructor(map);
		return (NO_COLLECTIBLE);
	}
	return (0);
}

int	check_solvable(t_map *map)
{
	int		**visited;
	int		i;
	t_state	st;

	st.exit_found = 0;
	st.collectibles_found = 0;
	visited = malloc(sizeof(int *) * map->height);
	if (!visited)
		return (MEMORY_ALLOCATION_FAILURE);
	i = 0;
	while (i < map->height)
	{
		visited[i] = calloc(map->width, sizeof(int));
		if (!visited[i])
			return (MEMORY_ALLOCATION_FAILURE);
		i++;
	}
	dfs(visited, map, map->player.position, &st);
	free_visited(visited, map->height);
	return (validate_result(map, st));
}
