/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:34:26 by anikoyan          #+#    #+#             */
/*   Updated: 2025/06/26 17:18:24 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_clear_image(t_image *image)
{
	int	x;
	int	y;
	
	y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 800)
		{
			int	offset = (y * image->line_length) + (x * (image->bits_per_pixel / 8));
			*(unsigned int *)(image->address + offset) = 0x000000;
		}
	}
}

static void	ft_pixel_color(int x, int y, t_image *image, int color)
{
	int	offset;

	offset = (y * image->line_length) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)(image->address + offset) = color;
}

static void	compute_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	double		z_re_sq, z_im_sq, two_z_re_z_im;
	int			i;
	const double	escape_val = fractal->escape_value;
	const int	max_iter = fractal->iterations_definition;
	const double	color_factor = 16777215.0 / max_iter;

	z.re = (ft_scale(x, -2, +2, 799) * fractal->zoom) + fractal->shift_x;
	z.im = (ft_scale(y, +2, -2, 799) * fractal->zoom) + fractal->shift_y;
	
	if (fractal->name[0] == 'J')
	{
		c.re = fractal->julia_re;
		c.im = fractal->julia_im;
	}
	else
	{
		c.re = z.re;
		c.im = z.im;
		z.re = 0;
		z.im = 0;
	}
	
	double z_re = z.re;
	double z_im = z.im;
	double c_re = c.re;
	double c_im = c.im;
	
	i = -1;
	while (++i < max_iter)
	{
		z_re_sq = z_re * z_re;
		z_im_sq = z_im * z_im;
		if (z_re_sq + z_im_sq > escape_val)
		{
			ft_pixel_color(x, y, &fractal->image, (int)(i * color_factor));
			return;
		}
		two_z_re_z_im = 2.0 * z_re * z_im;
		z_re = z_re_sq - z_im_sq + c_re;
		z_im = two_z_re_z_im + c_im;
	}
	ft_pixel_color(x, y, &fractal->image, 0xccff00);
}

void	ft_fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	ft_clear_image(&fractal->image);
	y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 800)
		{
			compute_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->image.image, 0, 0);
}
