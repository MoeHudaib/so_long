/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:00:43 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 19:41:06 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	down(t_minilibx *data, int old_x, int old_y)
{
	int	new_x;
	int	new_y;

	new_x = data->map.player.position.x;
	new_y = data->map.player.position.y;
	draw_image_32(data, "srcs/images/others/0.xpm", old_x * 32, old_y * 32);
	draw_image_32(data, "srcs/images/down/down1.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/down/down2.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/down/down3.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/down/down4.xpm", new_x * 32, new_y * 32);
}

void	up(t_minilibx *data, int old_x, int old_y)
{
	int	new_x;
	int	new_y;

	new_x = data->map.player.position.x;
	new_y = data->map.player.position.y;
	draw_image_32(data, "srcs/images/others/0.xpm", old_x * 32, old_y * 32);
	draw_image_32(data, "srcs/images/up/up1.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/up/up2.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/up/up3.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/up/up4.xpm", new_x * 32, new_y * 32);
}

void	right(t_minilibx *data, int old_x, int old_y)
{
	int	new_x;
	int	new_y;

	new_x = data->map.player.position.x;
	new_y = data->map.player.position.y;
	draw_image_32(data, "srcs/images/others/0.xpm", old_x * 32, old_y * 32);
	draw_image_32(data, "srcs/images/right/right1.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/right/right2.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/right/right3.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/right/right4.xpm", new_x * 32, new_y * 32);
}

void	left(t_minilibx *data, int old_x, int old_y)
{
	int	new_x;
	int	new_y;

	new_x = data->map.player.position.x;
	new_y = data->map.player.position.y;
	draw_image_32(data, "srcs/images/others/0.xpm", old_x * 32, old_y * 32);
	draw_image_32(data, "srcs/images/left/left1.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/left/left2.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/left/left3.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/left/left4.xpm", new_x * 32, new_y * 32);
}
