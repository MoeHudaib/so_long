/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:04 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 16:12:08 by mohammad         ###   ########.fr       */
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
