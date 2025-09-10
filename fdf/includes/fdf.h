#ifndef FDF_H
#define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "../libft/libft.h"
#include "../GNL/get_next_line.h"

typedef struct s_point {
    int x;
    int y;
    int z;
} t_point;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		**z_matrix;
	int		zoom;
	int		shift_x;
	int		shift_y;
	int		z_min;
	int		z_max;
}	t_fdf;

void draw(t_fdf *data, int zoom);
void read_map(char *file, t_fdf *data);
int	get_color(int z, int z_min, int z_max);

#endif
