/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:10:18 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/09/19 23:00:13 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map	map_constructor(char *filename)
{
	t_map	map;
	int		checker;

	checker = get_map_hw(filename, &map);
	if (checker < 0)
		error_type(checker, &map);
	checker = set_map_grid(filename, &map);
	if (checker < 0)
		error_type(checker, &map);
	checker = map_validator(&map);
	if (checker < 0)
	{
		map_destructor(&map);
		error_type(checker, &map);
	}
	get_grid_stats(&map);
	checker = walls_checker(&map);
	if (checker < 0)
		error_type(checker, &map);
	checker = check_solvable(&map);
	if (checker < 0)
		error_type(checker, &map);
	return (map);
}

void	map_destructor(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		free_tokens(map->grid);
	return ;
}

static void	error_type2(int error_type)
{
	if (error_type == INVALID_WIDTH)
		ft_printf("Error: Invalid map width.\n");
	else if (error_type == INVALID_HEIGHT)
		ft_printf("Error: Invalid map height.\n");
	else if (error_type == INVALID_LINE_LENGTH)
		ft_printf("Error: Inconsistent line length in map.\n");
	else if (error_type == INVALID_CHARACTER)
		ft_printf("Error: Invalid character found in map.\n");
	else if (error_type == MULTIPLE_PLAYERS)
		ft_printf("Error: Multiple players defined in map.\n");
	else if (error_type == NO_PLAYER)
		ft_printf("Error: No player defined in map.\n");
	else if (error_type == NO_EXIT)
		ft_printf("Error: No exit defined in map.\n");
	else if (error_type == NO_COLLECTIBLE)
		ft_printf("Error: No collectible found in map.\n");
	else if (error_type == MEMORY_ALLOCATION_FAILURE)
		ft_printf("Error: Memory allocation failure.\n");
	else
		ft_printf("Error: Unknown error.\n");
}

void	error_type(int error_type, t_map *map)
{
	(void)map;
	if (error_type == INVALID_FILE)
		ft_printf("Error: Invalid file provided.\n");
	else if (error_type == INVALID_XPM_FILE)
		ft_printf("Error: Invalid XPM file provided.\n");
	else if (error_type == INVALID_FILE_NAME)
		ft_printf("Error: Invalid file name.\n");
	else if (error_type == INVLAID_GRID)
		ft_printf("Error: Invalid grid.\n");
	else if (error_type == INVALID_LINE)
		ft_printf("Error: Invalid line in map.\n");
	else if (error_type == MUTLIPLE_EXITS)
		ft_printf("Error: Multiple exits defined in map.\n");
	else
		error_type2(error_type);
	exit(EXIT_FAILURE);
}
