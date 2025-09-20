/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:53 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 17:18:36 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "player.h"
# include "input.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

typedef enum e_error_type
{
	INVALID_FILE = -42,
	INVALID_XPM_FILE,
	INVALID_WIDTH,
	INVALID_FILE_NAME,
	INVLAID_GRID,
	INVALID_HEIGHT,
	INVALID_LINE_LENGTH,
	INVALID_CHARACTER,
	INVALID_LINE,
	MULTIPLE_PLAYERS,
	MUTLIPLE_EXITS,
	NO_PLAYER,
	NO_EXIT,
	NO_COLLECTIBLE,
	MEMORY_ALLOCATION_FAILURE,
	NOT_AVAILABLE
}	t_error_type;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			player_count;
	int			exit_count;
	t_player	player;
	t_point		sb_posistion;
	int			enemy_count;
}	t_map;

typedef struct s_state
{
	int	exit_found;
	int	collectibles_found;
}	t_state;

int		get_map_hw(const char *filename, t_map *map);
void	free_tokens(char **tokens);
int		set_map_grid(const char *filename, t_map *map);
void	free_grid(char **grid, int count);
int		walls_checker(t_map *map);
int		map_validator(t_map *map);
t_map	map_constructor(char *filename);
void	map_destructor(t_map *map);
void	error_type(int error_type, t_map *map);
void	get_grid_stats(t_map *map);
int		ft_strlen_no_nl(const char *str);
int		check_solvable(t_map *map);
int		is_in_set(char c, char *set);

#endif
