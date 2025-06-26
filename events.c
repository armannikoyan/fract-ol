/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:29:37 by anikoyan          #+#    #+#             */
/*   Updated: 2025/06/26 17:11:49 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_image(fractal->mlx_connection, fractal->image.image);
	exit(0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == 53)
		close_handler(fractal);
	else if (keysym == 123)
		fractal->shift_x += 0.15 * fractal->zoom;
	else if (keysym == 124)
		fractal->shift_x -= 0.15 * fractal->zoom;
	else if (keysym == 125)
		fractal->shift_y += 0.15 * fractal->zoom;
	else if (keysym == 126)
		fractal->shift_y -= 0.15 * fractal->zoom;
	else if (keysym == 30 && fractal->iterations_definition < 200)
		fractal->iterations_definition += 5;
	else if (keysym == 33 && fractal->iterations_definition > 5)
		fractal->iterations_definition -= 5;
	ft_fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double zoom_factor = 1.05;
	double mouse_re = ft_scale(x, -2, +2, 799);
	double mouse_im = ft_scale(y, +2, -2, 799); // Corrected Y-axis
	
	double old_zoom = fractal->zoom;
	
	if (button == 4)
	{
		fractal->zoom *= zoom_factor;
		fractal->shift_x += mouse_re * (old_zoom - fractal->zoom);
		fractal->shift_y += mouse_im * (old_zoom - fractal->zoom);
	}
	else if (button == 5)
	{
		fractal->zoom /= zoom_factor;
		fractal->shift_x += mouse_re * (old_zoom - fractal->zoom);
		fractal->shift_y += mouse_im * (old_zoom - fractal->zoom);
	}
	ft_fractal_render(fractal);
	return (0);
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (fractal->name[0] == 'J')
	{
		fractal->julia_re = (ft_scale(x, -2, +2, 799) * fractal->zoom)
			+ fractal->shift_x;
		fractal->julia_im = (ft_scale(y, +2, -2, 799) * fractal->zoom)
			+ fractal->shift_y;
		ft_fractal_render(fractal);
	}
	return (0);
}
