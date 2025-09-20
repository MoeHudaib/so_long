/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:49:10 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 17:28:37 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_minilibx	data;

	if (argc != 2)
	{
		ft_printf("Error\nInvalid number of arguments.\n");
		return (1);
	}
	map = map_constructor(argv[1]);
	data = mlx_cons(&map, map.height * 32, map.width * 32, "Test");
	data.mlx = mlx_init();
	if (data.mlx)
		data.win = mlx_new_window(data.mlx, data.width, data.height, data.label);
	if (!data.mlx || !data.win)
	{
		minilibx_destructor(&data);
		return (1);
	}
	draw_map(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, animate_all, &data);
	mlx_loop(data.mlx);
	minilibx_destructor(&data);
	return (0);
}
