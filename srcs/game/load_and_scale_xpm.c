/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_and_scale_xpm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:08:35 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/19 21:10:29 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	init_scaled_image(void *mlx, t_image_data *scaled)
{
	scaled->img = mlx_new_image(mlx, 32, 32);
	if (!scaled->img)
		return (1);
	scaled->addr = mlx_get_data_addr(scaled->img, &scaled->bpp,
			&scaled->line_length, &scaled->endian);
	scaled->width = 32;
	scaled->height = 32;
	return (0);
}

static void	scale_pixel(t_image_data *src, t_image_data *dst, int x, int y)
{
	int	src_x;
	int	src_y;
	int	s_p;
	int	d_p;

	src_x = x * src->width / 32;
	if (src_x >= src->width)
		src_x = src->width - 1;
	src_y = y * src->height / 32;
	if (src_y >= src->height)
		src_y = src->height - 1;
	s_p = src_y * src->line_length + src_x * (src->bpp / 8);
	d_p = y * dst->line_length + x * (dst->bpp / 8);
	*(unsigned int *)(dst->addr + d_p) = *(unsigned int *)(src->addr + s_p);
}

static void	copy_scaled_pixels(t_image_data *src, t_image_data *dst)
{
	int	x;
	int	y;

	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			scale_pixel(src, dst, x, y);
			x++;
		}
		y++;
	}
}

t_image_data	load_and_scale_xpm(void *mlx, char *filename)
{
	t_image_data	original;
	t_image_data	scaled;

	scaled.img = NULL;
	if (!mlx || !filename)
		return (scaled);
	original.img = mlx_xpm_file_to_image(mlx, filename,
			&original.width, &original.height);
	if (!original.img)
		return (scaled);
	original.addr = mlx_get_data_addr(original.img, &original.bpp,
			&original.line_length, &original.endian);
	if (init_scaled_image(mlx, &scaled))
	{
		mlx_destroy_image(mlx, original.img);
		return (scaled);
	}
	copy_scaled_pixels(&original, &scaled);
	mlx_destroy_image(mlx, original.img);
	return (scaled);
}
