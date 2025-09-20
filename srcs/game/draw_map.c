/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:06:23 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 18:39:49 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	draw_health_bar(t_minilibx *data, int i, int *j)
{
	data->map.sb_posistion.x = *j;
	data->map.sb_posistion.y = i;
	draw_image_96x32(data,
		"srcs/images/health_bar/h1.xpm",
		*j * 32,
		i * 32);
	*j += 2;
}

static void	draw_coin(t_minilibx *data, int j, int i)
{
	char	*coin_files[5];
	int		idx;

	coin_files[0] = "srcs/images/coin/C1.xpm";
	coin_files[1] = "srcs/images/coin/C2.xpm";
	coin_files[2] = "srcs/images/coin/C3.xpm";
	coin_files[3] = "srcs/images/coin/C4.xpm";
	coin_files[4] = "srcs/images/coin/C5.xpm";
	draw_image_32(data, "srcs/images/coin/C1.xpm", j * 32, i * 32);
	idx = data->anim_count;
	data->anims[idx] = init_anim(coin_files, 5, j, i);
	data->anim_count++;
}

static void	draw_enemy(t_minilibx *data, int j, int i)
{
	char	*enemy_files[12];
	int		idx;

	enemy_files[0] = "srcs/images/enemy/N1.xpm";
	enemy_files[1] = "srcs/images/enemy/N2.xpm";
	enemy_files[2] = "srcs/images/enemy/N3.xpm";
	enemy_files[3] = "srcs/images/enemy/N4.xpm";
	enemy_files[4] = "srcs/images/enemy/N5.xpm";
	enemy_files[5] = "srcs/images/enemy/N6.xpm";
	enemy_files[6] = "srcs/images/enemy/N7.xpm";
	enemy_files[7] = "srcs/images/enemy/N8.xpm";
	enemy_files[8] = "srcs/images/enemy/N9.xpm";
	enemy_files[9] = "srcs/images/enemy/N10.xpm";
	enemy_files[10] = "srcs/images/enemy/N11.xpm";
	enemy_files[11] = "srcs/images/enemy/N12.xpm";
	draw_image_32(data, "srcs/images/enemy/N1.xpm", j * 32, i * 32);
	idx = data->anim_count;
	data->anims[idx] = init_anim(enemy_files, 12, j, i);
	data->anim_count++;
}

static void	draw_tile(t_minilibx *data, char c, int j, int i)
{
	if (c == '1')
		draw_image_32(data, "srcs/images/others/1.xpm", j * 32, i * 32);
	else if (c == '0')
		draw_image_32(data, "srcs/images/others/0.xpm", j * 32, i * 32);
	else if (c == 'E')
		draw_image_32(data, "srcs/images/others/E.xpm", j * 32, i * 32);
	else if (c == 'P')
		draw_image_32(data, "srcs/images/down/down1.xpm", j * 32, i * 32);
	else if (c == 'C')
		draw_coin(data, j, i);
	else if (c == 'N')
		draw_enemy(data, j, i);
	else
		draw_image_32(data, "srcs/images/others/0.xpm", j * 32, i * 32);
}

int	draw_map(t_minilibx *data)
{
	int		i;
	int		j;
	char	c;

	if (!data || !data->map.grid)
		return (INVALID_FILE);
	i = 0;
	while (i < data->map.height && data->map.grid[i])
	{
		j = 0;
		while (j < data->map.width && data->map.grid[i][j])
		{
			c = data->map.grid[i][j];
			if (i == 0 && j == 3)
			{
				draw_health_bar(data, i, &j);
				j++;
				continue ;
			}
			draw_tile(data, c, j, i);
			j++;
		}
		i++;
	}
	return (0);
}
