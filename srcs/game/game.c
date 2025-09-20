/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:00:48 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 18:28:51 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	draw_image_32(t_minilibx *data, char *filename, int x, int y)
{
	t_image_data	sprite;

	if (!data || !data->mlx || !data->win)
		return (INVALID_FILE);
	sprite = load_and_scale_xpm(data->mlx, filename);
	if (sprite.img)
	{
		mlx_put_image_to_window(data->mlx, data->win, sprite.img, x, y);
		mlx_destroy_image(data->mlx, sprite.img);
	}
	return (0);
}

int	animate_all(t_minilibx *data)
{
	int	i;

	if (!data || data->anim_count <= 0)
		return (0);
	i = 0;
	while (i < data->anim_count)
	{
		if (data->anims[i])
			update_anim(data, data->anims[i]);
		i++;
	}
	return (0);
}

void	print_steps(t_minilibx *data)
{
	char	*steps_str;
	char	*msg;

	if (!data || !data->mlx || !data->win)
		return ;
	steps_str = ft_itoa(data->map.player.steps);
	if (!steps_str)
		return ;
	msg = ft_strjoin("Steps: ", steps_str);
	free(steps_str);
	if (!msg)
		return ;
	draw_image_32(data, "srcs/images/others/1.xpm", 0, 0);
	draw_image_32(data, "srcs/images/others/1.xpm", 32, 0);
	mlx_string_put(data->mlx, data->win, 0, 16, 0xFFFFFF, msg);
	free(msg);
}
