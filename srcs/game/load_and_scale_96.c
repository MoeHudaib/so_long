/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_and_scale_96.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:04:01 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:06:05 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static t_image_data	init_scaled_image(void *mlx, int width, int height)
{
	t_image_data	scaled;

	scaled.img = mlx_new_image(mlx, width, height);
	if (!scaled.img)
		return (scaled);
	scaled.addr = mlx_get_data_addr(scaled.img, &scaled.bpp,
			&scaled.line_length, &scaled.endian);
	scaled.width = width;
	scaled.height = height;
	return (scaled);
}

static void	copy_one_pixel(t_image_data *src, t_image_data *dst, int x, int y)
{
	int	src_x;
	int	src_y;
	int	s_p;
	int	d_p;

	src_x = x * src->width / dst->width;
	src_y = y * src->height / dst->height;
	s_p = src_y * src->line_length + src_x * (src->bpp / 8);
	d_p = y * dst->line_length + x * (dst->bpp / 8);
	*(unsigned int *)(dst->addr + d_p) = *(unsigned int *)(src->addr + s_p);
}

static void	copy_scaled_pixels(t_image_data *src, t_image_data *dst)
{
	int	x;
	int	y;

	y = 0;
	while (y < dst->height)
	{
		x = 0;
		while (x < dst->width)
		{
			copy_one_pixel(src, dst, x, y);
			x++;
		}
		y++;
	}
}

t_image_data	load_and_scale_xpm_96x32(void *mlx, char *filename)
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
	scaled = init_scaled_image(mlx, 96, 32);
	if (!scaled.img)
	{
		mlx_destroy_image(mlx, original.img);
		return (scaled);
	}
	copy_scaled_pixels(&original, &scaled);
	mlx_destroy_image(mlx, original.img);
	return (scaled);
}
