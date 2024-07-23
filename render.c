/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:34:26 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/23 15:12:07 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_fractal_type(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (fractal->name[0] == 'J')
	{
		c->re = fractal->julia_re;
		c->im = fractal->julia_im;
		return ;
	}
	c->re = z->re;
	c->im = z->im;
}

static void	ft_pixel_color(int x, int y, t_image *image, int color)
{
	int	offset;

	offset = (y * image->line_length) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)(image->address + offset) = color;
}

static void	handle_address(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.re = (ft_scale(x, -2, +2, 799) * fractal->zoom) + fractal->shift_x;
	z.im = (ft_scale(y, +2, -2, 799) * fractal->zoom) + fractal->shift_y;
	ft_fractal_type(&z, &c, fractal);
	while (i < fractal->iterations_definition)
	{
		z = ft_sum(ft_multiply(z, z), c);
		if ((z.re * z.re) + (z.im * z.im) > fractal->escape_value)
		{
			color = ft_scale(i, 0x000000, 0xffffff,
					fractal->iterations_definition);
			ft_pixel_color(x, y, &fractal->image, color);
			return ;
		}
		++i;
	}
	ft_pixel_color(x, y, &fractal->image, 0xccff00);
}

void	ft_fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 800)
			handle_address(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->image.image, 0, 0);
}
