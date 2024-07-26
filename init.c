/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:56:51 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/26 13:18:23 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	perror("Malloc error: ");
	exit(1);
}

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iterations_definition = 150;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1.0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, 2, 0, key_handler, fractal);
	mlx_hook(fractal->mlx_window, 4, 0, mouse_handler, fractal);
	mlx_hook(fractal->mlx_window, 17, 0, close_handler, fractal);
}

void	ft_fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (NULL == fractal->mlx_connection)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, 800,
			800, fractal->name);
	if (NULL == fractal->mlx_window)
		malloc_error();
	fractal->image.image = mlx_new_image(fractal->mlx_connection, 800, 800);
	if (NULL == fractal->image.image)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		malloc_error();
	}
	fractal->image.address = mlx_get_data_addr(fractal->image.image,
			&fractal->image.bits_per_pixel,
			&fractal->image.line_length, &fractal->image.endian);
	if (NULL == fractal->image.address)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_image(fractal->mlx_connection, fractal->image.image);
		malloc_error();
	}
	events_init(fractal);
	data_init(fractal);
}
