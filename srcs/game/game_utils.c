#include "game.h"

int close_window(t_minilibx *data)
{
    // Free map memory
    map_destructor(&data->map);

    // Destroy window if it exists
    if (data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        data->win = NULL;
    }

    // Destroy display + free mlx pointer (Linux)
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }

    exit(0); // clean exit
    return (0);
}

int game_over(t_map *map, int win)
{
    if (win)
        write(1, "You Win!\n", 9);
    else
        write(1, "Game Over!\n", 11);

    // free map (but don’t kill mlx here, let close_window handle it)
    map_destructor(map);

    exit(0); // terminate program
    return (0);
}

t_image_data load_and_scale_xpm_96x32(void *mlx, char *filename)
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

    // Create scaled 96x32 image
    scaled.img = mlx_new_image(mlx, 96, 32);
    if (!scaled.img)
    {
        mlx_destroy_image(mlx, original.img);
        scaled.img = NULL;
        return scaled;
    }
    scaled.addr = mlx_get_data_addr(scaled.img, &scaled.bpp,
                                    &scaled.line_length, &scaled.endian);
    scaled.width = 96;
    scaled.height = 32;

    // Scale image (nearest neighbor)
    for (y = 0; y < 32; y++)
    {
        for (x = 0; x < 96; x++)
        {
            int src_x = x * original.width / 96;
            int src_y = y * original.height / 32;
            int src_pos = src_y * original.line_length + src_x * (original.bpp / 8);
            int dst_pos = y * scaled.line_length + x * (scaled.bpp / 8);
            *(unsigned int *)(scaled.addr + dst_pos) = *(unsigned int *)(original.addr + src_pos);
        }
    }

    // Clean up original image
    mlx_destroy_image(mlx, original.img);
    return scaled;
}

/* -------------------------------------------------- */
/* Draw a 96x32 sprite (like health bar)             */
/* -------------------------------------------------- */
int draw_image_96x32(t_minilibx *data, char *filename, int x, int y)
{
    if (!data || !data->mlx || !data->win)
        return (INVALID_FILE);

    t_image_data sprite = load_and_scale_xpm_96x32(data->mlx, filename);
    if (sprite.img)
    {
        mlx_put_image_to_window(data->mlx, data->win, sprite.img, x, y);
        mlx_destroy_image(data->mlx, sprite.img);
    }

    return (0);
}
