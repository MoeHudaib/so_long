/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:49:10 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/21 17:03:22 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	check(char *str1, char *str2)
{
	int	checker;

	checker = ft_strncmp(str1 + (ft_strlen(str1) - 4), str2, 4);
	return (checker);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_minilibx	data;

	if (argc != 2)
		return (error_type(INVALID_NUMBER_OF_ARGUMENTS, NULL));
	if (check(argv[1], ".ber"))
		return (error_type(INVALID_XPM_FILE, NULL));
	map = map_constructor(argv[1]);
	data = mlx_cons(&map, map.height * 32, map.width * 32, "Test");
	data.mlx = mlx_init();
	if (!data.mlx)
		minilibx_destructor(&data, MEMORY_ALLOCATION_FAILURE);
	data.win = mlx_new_window(data.mlx, data.width, data.height, data.label);
	if (!data.win)
		minilibx_destructor(&data, MEMORY_ALLOCATION_FAILURE);
	draw_map(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, animate_all, &data);
	mlx_loop(data.mlx);
	minilibx_destructor(&data, 0);
}
