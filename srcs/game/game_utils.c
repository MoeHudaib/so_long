/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:00:52 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/21 12:48:39 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_minilibx *data)
{
	minilibx_destructor(data, 0);
	exit(0);
	return (0);
}

int	game_over(t_minilibx *data, int win)
{
	data->map.player.steps++;
	ft_printf("steps: %d\n", data->map.player.steps);
	if (win)
		write(1, "You Win!\n", 9);
	else
		write(1, "Game Over!\n", 11);
	minilibx_destructor(data, 0);
	exit(0);
	return (0);
}

int	draw_image_96x32(t_minilibx *data, char *filename, int x, int y)
{
	t_image_data	sprite;

	if (!data || !data->mlx || !data->win)
		return (INVALID_FILE);
	sprite = load_and_scale_xpm_96x32(data->mlx, filename);
	if (sprite.img)
	{
		mlx_put_image_to_window(data->mlx, data->win, sprite.img, x, y);
		mlx_destroy_image(data->mlx, sprite.img);
	}
	return (0);
}
