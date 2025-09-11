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
    // p->x = (x - z) * cos(angle);
    // p->y= y + (x - z) * sin(angle);
}

struct libmix
{
    void *mlx;
    void *win;
    int  horizontal;
    int  vertical;
    int  color;
};

struct matrix
{
    int xs;
    int ys;
    int spacing;
};

void    draw_pixel(struct matrix matrix_, struct libmix data)
{
    for (int y = 0; y < matrix_.ys; y++)
    {
        for (int x = 0; x < matrix_.xs; x++)
        {
            struct t_point p;
            p.x = x * matrix_.spacing;
            p.y = y * matrix_.spacing;

            // Simulate a "hole" by lowering z in the center
            int dx = x - matrix_.xs / 2;
            int dy = y - matrix_.ys / 2;
            p.z = ((dx * dx + dy * dy) / 5); // Makes a dip in center

            apply_isometric(&p);

            // Offset to center on screen
            data.horizontal = p.x + 400;
            data.vertical = p.y + 400;
            data.color = 0xFFFFFF;

            mlx_pixel_put(data.mlx, data.win, data.horizontal, data.vertical, data.color);
        }
    }

};

int main()
{
    struct libmix data;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 800, 800, "Isometric Hole");
    struct matrix matrix_;
    matrix_.xs = 20;
    matrix_.ys = 20;
    matrix_.spacing = 10;
    draw_pixel(matrix_, data);
    mlx_loop(data.mlx);
    return 0;
}

