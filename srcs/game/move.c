/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:23:05 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 13:26:56 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	free_animations(t_minilibx *data, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < data->anim_count)
	{
		t_anim *anim = data->anims[i];
		if (anim && anim->x == x && anim->y == y)
		{
			free(anim->frames);
			free(anim);
			j = i;
			while (j < data->anim_count - 1)
			{
				data->anims[j] = data->anims[j + 1];
				j++;
			}
			data->anims[data->anim_count - 1] = NULL;
			data->anim_count--;
			return (1);
		}
		i++;
	}
	return (0);
}

void	handle_enemy(t_minilibx *data, int new_x, int new_y)
{
	if (!data)
		return ;
	draw_image_32(data, "srcs/images/up/hurt.xpm", new_x * 32, new_y * 32);
	data->map.player.health -= 50;
	if (data->map.player.health <= -50)
	{
		game_over(data, 0);
		return ;
	}
	else if (data->map.player.health == 50)
		draw_image_96x32(data, "srcs/images/health_bar/h2.xpm",
			data->map.sb_posistion.x * 32, data->map.sb_posistion.y * 32);
	else
		draw_image_96x32(data, "srcs/images/health_bar/h3.xpm",
			data->map.sb_posistion.x * 32, data->map.sb_posistion.y * 32);
	free_animations(data, new_x, new_y);
	draw_image_32(data, "srcs/images/enemy/N13.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/enemy/N14.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/enemy/N15.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/enemy/N16.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/enemy/N17.xpm", new_x * 32, new_y * 32);
	draw_image_32(data, "srcs/images/enemy/N18.xpm", new_x * 32, new_y * 32);
}

void	handle_rest(t_minilibx *data, int new_x, int new_y, int movement_type)
{
	int old_x;
	int old_y;

	if (!data)
		return ;
	old_x = data->map.player.position.x;
	old_y = data->map.player.position.y;
	data->map.grid[old_y][old_x] = '0';
	data->map.grid[new_y][new_x] = 'P';
	data->map.player.position.x = new_x;
	data->map.player.position.y = new_y;
	data->map.player.steps++;
	draw_image_32(data, "srcs/images/others/0.xpm", old_x * 32, old_y * 32);
	ft_printf("steps: %d\n", data->map.player.steps);
	if (movement_type == UP)
		up(data, old_x, old_y);
	else if (movement_type == DOWN)
		down(data, old_x, old_y);
	else if (movement_type == LEFT)
		left(data, old_x, old_y);
	else if (movement_type == RIGHT)
		right(data, old_x, old_y);
}

void move_player(t_minilibx *data, int dx, int dy, int movement_type)
{
    int old_x;
    int old_y;
    int new_x;
    int new_y;
    
    old_x = data->map.player.position.x;
    old_y = data->map.player.position.y;
    new_x = old_x + dx;
    new_y = old_y + dy;
    if (data->map.grid[new_y][new_x] == '1') // wall
        return;
    else if (data->map.grid[new_y][new_x] == 'E') // exit
    {
        if (data->map.collectibles == 0)
            game_over(data, 1);
    }
    else if (data->map.grid[new_y][new_x] == 'N') // enemy
        handle_enemy(data, new_x, new_y);
    else if (data->map.grid[new_y][new_x] == 'C') // collectible
    {
        data->map.collectibles--;
        free_animations(data, new_x, new_y);
    }
    handle_rest(data, new_x, new_y, movement_type);
}