/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:00:36 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 17:25:23 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_anims(t_minilibx *data)
{
	int	i;

	if (!data || !data->anims)
		return ;
	i = 0;
	while (i < data->anim_count)
	{
		if (data->anims[i])
		{
			if (data->anims[i]->frames)
				free(data->anims[i]->frames);
			free(data->anims[i]);
		}
		i++;
	}
	free(data->anims);
	data->anims = NULL;
	data->anim_count = 0;
}

void	free_minilibx(t_minilibx *data)
{
	if (!data)
		return ;
	free_anims(data);
}

t_minilibx	mlx_cons(t_map *map, int height, int width, char *label)
{
	t_minilibx	data;

	data.height = height;
	data.width = width;
	data.label = label;
	data.map = *map;
	data.mlx = NULL;
	data.win = NULL;
	data.anim_count = 0;
	data.anims = malloc(sizeof(t_anim *) * 25);
	if (!data.anims)
		return (data);
	return (data);
}

void	minilibx_destructor(t_minilibx *data)
{
	if (!data)
		return ;
	if (data->map.grid)
	{
		map_destructor(&data->map);
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	if (data->anims)
	{
		free_minilibx(data);
	}
}

int	handle_key(int keycode, t_minilibx *data)
{
	if (keycode == KEY_W)
		move_player(data, 0, -1, UP);
	else if (keycode == KEY_A)
		move_player(data, -1, 0, LEFT);
	else if (keycode == KEY_S)
		move_player(data, 0, 1, DOWN);
	else if (keycode == KEY_D)
		move_player(data, 1, 0, RIGHT);
	else if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}
