#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include "includes/fdf.h"

void apply_isometric(struct t_point *p)
{
    double angle = 30* M_PI / 180;
    int x = p->x;
    int y = p->y;
    int z = p->z;

    p->x = (x - y) * cos(angle);
    p->y = (x + y) * sin(angle) - z;
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 800, "Isometric Hole");

    int grid_size = 20;
    int spacing = 10;

    for (int y = 0; y < grid_size; y++)
    {
        for (int x = 0; x < grid_size; x++)
        {
            struct t_point p;
            p.x = x * spacing;
            p.y = y * spacing;

            // Simulate a "hole" by lowering z in the center
            int dx = x - grid_size / 2;
            int dy = y - grid_size / 2;
            p.z = ((dx * dx + dy * dy) / 5); // Makes a dip in center

            apply_isometric(&p);

            // Offset to center on screen
            int screen_x = p.x + 400;
            int screen_y = p.y + 400;

            mlx_pixel_put(mlx, win, screen_x, screen_y, 0xFFFFFF);
        }
    }

    mlx_loop(mlx);
    return 0;
}

