/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:00:52 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:00:53 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_minilibx *data)
{
	minilibx_destructor(data);
	exit(0);
	return (0);
}

int	game_over(t_minilibx *data, int win)
{
	if (win)
		write(1, "You Win!\n", 9);
	else
		write(1, "Game Over!\n", 11);
	minilibx_destructor(data);
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
