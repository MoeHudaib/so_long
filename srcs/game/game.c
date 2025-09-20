/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:00:48 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:00:49 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int draw_image_32(t_minilibx *data, char *filename, int x, int y)
{
    if (!data || !data->mlx || !data->win)
        return (INVALID_FILE);
    t_image_data sprite = load_and_scale_xpm(data->mlx, filename);
    if (sprite.img)
    {
        mlx_put_image_to_window(data->mlx, data->win, sprite.img, x, y);
        mlx_destroy_image(data->mlx, sprite.img);
    }
    return (0);
}

int animate_all(t_minilibx *data)
{
    if (!data || data->anim_count <= 0)
        return (0);
    for (int i = 0; i < data->anim_count; i++)
    {
        if (data->anims[i])
            update_anim(data, data->anims[i]);
    }
    return (0);
}

int main(void)
{
    t_map map;
    map = map_constructor("srcs/map/hello.ber");
    printf("Height: %d\nWIDTH: %d\n", map.height, map.width);
    t_minilibx data;
    data = minilibx_constructor(&map, map.height * 32, map.width * 32, "Test");
    data.mlx = mlx_init();
    if (!data.mlx)
    {
        map_destructor(&map);
        return (1);
    }
    data.win = mlx_new_window(data.mlx, data.width, data.height, data.label);
    if (!data.win)
    {
        free(data.mlx);
        map_destructor(&map);
        return (1);
    }
    draw_map(&data);
    mlx_hook(data.win, 2, 1L<<0, handle_key, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop_hook(data.mlx, animate_all, &data);
    mlx_loop(data.mlx);
    minilibx_destructor(&data);
    return (0);
}
