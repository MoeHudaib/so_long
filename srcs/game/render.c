/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:04 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/21 12:20:05 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_anim	*init_anim(char **files, int frame_count, int x, int y)
{
	t_anim	*anim;
	int		i;

	anim = malloc(sizeof(t_anim));
	if (!anim)
		return (NULL);
	anim->frames = malloc(sizeof(char *) * frame_count);
	if (!anim->frames)
	{
		free(anim);
		return (NULL);
	}
	i = -1;
	while (++i < frame_count)
		anim->frames[i] = files[i];
	anim->frame_count = frame_count;
	anim->frame = 0;
	anim->speed = 12000;
	anim->counter = 0;
	anim->x = x;
	anim->y = y;
	return (anim);
}

void	render_anim(t_minilibx *data, t_anim *anim)
{
	if (!anim || !anim->frames || !data)
		return ;
	draw_image_32(data, anim->frames[anim->frame], anim->x * 32, anim->y * 32);
}

void	update_anim(t_minilibx *data, t_anim *anim)
{
	if (!anim)
		return ;
	anim->counter++;
	if (anim->counter >= anim->speed)
	{
		anim->counter = 0;
		anim->frame = (anim->frame + 1) % anim->frame_count;
		render_anim(data, anim);
	}
}

void	walk_through_exit(int new_x, int new_y, t_minilibx *data)
{
	int	x;
	int	y;

	if (data->map.grid[new_y][new_x] == 'E')
	{
		if (data->map.collectibles == 0)
			game_over(data, 1);
		data->map.exit_pose.x = new_x;
		data->map.exit_pose.y = new_y;
	}
	x = data->map.exit_pose.x;
	y = data->map.exit_pose.y;
	if (new_x == x && new_y == y)
	{
		if (data->map.collectibles == 0)
			game_over(data, 1);
	}
}
