#include "fdf.h"
#include <stdio.h> // Needed for printf

int main(int argc, char **argv)
{
    t_fdf data;
    char    buf[1000];
    int     bytes = 0;
    if (argc != 2)
    {
        write(1, "Usage: ./fdf map.fdf\n", 22);
        return (1);
    }

    printf("[INFO] Reading map...\n");
    read_map(argv[1], &data);
    printf("[INFO] Map read successfully: width = %d, height = %d\n", data.width, data.height);

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 1000, 1000, "FdF");
    data.zoom = 20;
    data.shift_x = 300;
    data.shift_y = 300;

    printf("[INFO] Starting draw...\n");
	printf("[DEBUG] z_matrix:\n");
	for (int i = 0; i < data.height; i++) {
		for (int j = 0; j < data.width; j++) {
			printf("%d ", data.z_matrix[i][j]);
		}
		printf("\n");
	}
    read(1, buf, bytes);
    if (!*buf)
    {
        buf[0] = '9';
        buf[1] = '\0';
    }
    buf[bytes] = '\0';
    int tmp = ft_atoi(buf);
    data.zoom = tmp ? tmp : 20;
    draw(&data, data.zoom);
    printf("[INFO] Done drawing.\n");

    mlx_loop(data.mlx);
    return (0);
}
