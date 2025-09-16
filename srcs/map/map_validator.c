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
	return (0);
}

int	map_validator(t_map *map)
{
	int	i;
	int	j;
	int	height;
	int	p_flag;
	int	err;

	if (!map)
		return (INVLAID_GRID);
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
			if ((err = check_characters(map, i, j, &p_flag)) != 0)
				return (err);
	}
	if (map->height != height)
		return (INVALID_HEIGHT);
	if (!p_flag)
		return (NO_PLAYER);
	return (0);
}
#include "map.h"

void	get_grid_stats(t_map *map)
{
	int	i;
	int	j;

	map->collectibles = 0;
	map->enemy_count = 0;
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
#include "map.h"

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
	while (map->grid[++i])
	{
		j = -1;
		while (map->grid[i][++j])
			if ((err = check_edges(map, i, j)) != 0)
				return (err);
	}
	return (0);
}
