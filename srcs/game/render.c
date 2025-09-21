/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:04 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/21 16:15:10 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

static char	**init_anim_frames(char **files, int frame_count)
{
	char	**frames;
	int		i;

	frames = malloc(sizeof(char *) * frame_count);
	if (!frames)
		return (NULL);
	i = 0;
	while (i < frame_count)
	{
		frames[i] = files[i];
		if (!frames[i])
		{
			while (--i >= 0)
				free(frames[i]);
			free(frames);
			return (NULL);
		}
		i++;
	}
	return (frames);
}

t_anim	*init_anim(char **files, int frame_count, int x, int y)
{
	t_anim	*anim;

	anim = malloc(sizeof(t_anim));
	if (!anim)
		return (NULL);
	anim->frames = init_anim_frames(files, frame_count);
	if (!anim->frames)
	{
		free(anim);
		return (NULL);
	}
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
