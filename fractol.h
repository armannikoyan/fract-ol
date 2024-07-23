/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:43:27 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/23 15:12:35 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>

# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_image
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_fractal
{
	char		*name;
	void		*mlx_connection;
	void		*mlx_window;
	t_image		image;
	double		escape_value;
	int			iterations_definition;
	double		shift_x;
	double		shift_y;
	double		zoom;
	double		julia_re;
	double		julia_im;
}		t_fractal;

void		ft_fractal_init(t_fractal *fractal);
void		ft_fractal_render(t_fractal *fractal);

int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);

t_complex	ft_multiply(t_complex a, t_complex b);
t_complex	ft_sum(t_complex a, t_complex b);
double		ft_scale(double unscaled_num, double new_min,
				double new_max, double old_max);

#endif
