#include "game.h"

/* -------------------------------------------------- */
/* Utility: load and scale an XPM file safely         */
/* -------------------------------------------------- */
t_image_data load_and_scale_xpm(void *mlx, char *filename)
{
    t_image_data original;
    t_image_data scaled;
    int x, y;

    if (!mlx || !filename)
    {
        scaled.img = NULL;
        return scaled;
    }

    // Load original image
    original.img = mlx_xpm_file_to_image(mlx, filename, &original.width, &original.height);
    if (!original.img)
    {
        scaled.img = NULL;
        return scaled;
    }
    original.addr = mlx_get_data_addr(original.img, &original.bpp,
                                      &original.line_length, &original.endian);

    // Create scaled 32x32 image
    scaled.img = mlx_new_image(mlx, 32, 32);
    if (!scaled.img)
    {
        mlx_destroy_image(mlx, original.img);
        scaled.img = NULL;
        return scaled;
    }
    scaled.addr = mlx_get_data_addr(scaled.img, &scaled.bpp,
                                    &scaled.line_length, &scaled.endian);
    scaled.width = 32;
    scaled.height = 32;

    // Scale image (nearest neighbor)
    for (y = 0; y < 32; y++)
    {
        for (x = 0; x < 32; x++)
        {
            int src_x = x * original.width / 32;
            int src_y = y * original.height / 32;
            int src_pos = src_y * original.line_length + src_x * (original.bpp / 8);
            int dst_pos = y * scaled.line_length + x * (scaled.bpp / 8);
            *(unsigned int *)(scaled.addr + dst_pos) =
                *(unsigned int *)(original.addr + src_pos);
        }
    }

    // Clean up original image
    mlx_destroy_image(mlx, original.img);
    return scaled;
}

/* -------------------------------------------------- */
/* Draw a single tile                                 */
/* -------------------------------------------------- */
int draw_image_32(t_minilibx *data, char *filename, int x, int y)
{
    if (!data || !data->mlx || !data->win)
        return (INVALID_FILE);

    // Always draw base floor tile
    // t_image_data floor = load_and_scale_xpm(data->mlx, "srcs/images/others/0.xpm");
    // if (floor.img)
    // {
    // //    mlx_put_image_to_window(data->mlx, data->win, floor.img, x, y);
    //     mlx_destroy_image(data->mlx, floor.img);
    // }

    // Then overlay the target sprite
    t_image_data sprite = load_and_scale_xpm(data->mlx, filename);
    if (sprite.img)
    {
        mlx_put_image_to_window(data->mlx, data->win, sprite.img, x, y);
        mlx_destroy_image(data->mlx, sprite.img);
    }

    return (0);
}

/* -------------------------------------------------- */
/* Draw the whole map                                 */
/* -------------------------------------------------- */
int draw_map(t_minilibx *data)
{
    if (!data || !data->map.grid)
        return (INVALID_FILE);

    for (int i = 0; data->map.grid[i]; i++)
    {
        for (int j = 0; data->map.grid[i][j]; j++)
        {
            char c = data->map.grid[i][j];
            if (i == 0 && j == 3) // Draw health bar at fixed position
            {
                data->map.sb_posistion.x = j;
                data->map.sb_posistion.y = i;
                draw_image_96x32(data,
                                 "srcs/images/health_bar/h1.xpm",
                                 j * 32, i * 32);
                j += 2; // Skip next 3 columns
                continue;
            }
            if (c == '1')
                draw_image_32(data, "srcs/images/others/1.xpm", j * 32, i * 32);
            else if (c == '0')
                draw_image_32(data, "srcs/images/others/0.xpm", j * 32, i * 32);
            else if (c == 'E')
                draw_image_32(data, "srcs/images/others/E.xpm", j * 32, i * 32);
            else if (c == 'P')
                draw_image_32(data, "srcs/images/down/down1.xpm", j * 32, i * 32);
            else if (c == 'C')
            {
                draw_image_32(data, "srcs/images/coin/C1.xpm", j * 32, i * 32);
                char *coin_files[] = {
                "srcs/images/coin/C1.xpm",
                "srcs/images/coin/C2.xpm",
                "srcs/images/coin/C3.xpm",
                "srcs/images/coin/C4.xpm",
                "srcs/images/coin/C5.xpm"
                };

                t_anim *coin_anim = init_anim(coin_files, 5, 15000, j, i);
                data->anims[data->anim_count++] = coin_anim;
            }   
            else if (c == 'N')
            {
                draw_image_32(data, "srcs/images/enemy/N1.xpm", j * 32, i * 32);
                char *coin_files[] = {
                "srcs/images/enemy/N1.xpm",
                "srcs/images/enemy/N2.xpm",
                "srcs/images/enemy/N3.xpm",
                "srcs/images/enemy/N4.xpm",
                "srcs/images/enemy/N5.xpm",
                "srcs/images/enemy/N6.xpm",
                "srcs/images/enemy/N7.xpm",
                "srcs/images/enemy/N8.xpm",
                "srcs/images/enemy/N9.xpm",
                "srcs/images/enemy/N10.xpm",
                "srcs/images/enemy/N11.xpm",
                "srcs/images/enemy/N12.xpm"
                };

                t_anim *coin_anim = init_anim(coin_files, 12, 8000, j, i);
                data->anims[data->anim_count++] = coin_anim;
            }   
            else
                draw_image_32(data, "srcs/images/others/0.xpm", j *32, i * 32);
        }
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

/* -------------------------------------------------- */
/* Main                                               */
/* -------------------------------------------------- */
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
