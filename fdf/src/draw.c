// draw.c
#include "fdf.h"
#include <math.h>

void	isometric(int *x, int *y, int z)
{
	int previous_x = *x;
	int previous_y = *y;

	*x = (previous_x - previous_y) * cos(0.523599);
	*y = (previous_x + previous_y) * sin(0.523599) - z;
}

void	draw_line(int x0, int y0, int x1, int y1, int color, t_fdf *data)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	float x_inc = dx / steps;
	float y_inc = dy / steps;
	float x = x0;
	float y = y0;

	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw(t_fdf *data, int zoom)
{
	int x, y;
	int x0, y0, x1, y1;
	int z0, z1, color;

	for (y = 0; y < data->height; y++)
	{
		for (x = 0; x < data->width; x++)
		{
			// Horizontal line
			if (x < data->width - 1)
			{
				x0 = x * zoom;
				y0 = y * zoom;
				x1 = (x + 1) * zoom;
				y1 = y * zoom;
				z0 = data->z_matrix[y][x];
				z1 = data->z_matrix[y][x + 1];
				color = get_color((z0 + z1) / 2, data->z_min, data->z_max);
				isometric(&x0, &y0, z0);
				isometric(&x1, &y1, z1);
				x0 += data->shift_x;
				y0 += data->shift_y;
				x1 += data->shift_x;
				y1 += data->shift_y;
				draw_line(x0, y0, x1, y1, color, data);
			}

			// Vertical line
			if (y < data->height - 1)
			{
				x0 = x * zoom;
				y0 = y * zoom;
				x1 = x * zoom;
				y1 = (y + 1) * zoom;
				z0 = data->z_matrix[y][x];
				z1 = data->z_matrix[y + 1][x];
				color = get_color((z0 + z1) / 2, data->z_min, data->z_max);
				isometric(&x0, &y0, z0);
				isometric(&x1, &y1, z1);
				x0 += data->shift_x;
				y0 += data->shift_y;
				x1 += data->shift_x;
				y1 += data->shift_y;
				draw_line(x0, y0, x1, y1, color, data);
			}
		}
	}
}

