/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:42:34 by anikoyan          #+#    #+#             */
/*   Updated: 2024/07/23 14:34:34 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((2 == argc && !ft_strncmp(argv[1], "M", 1))
		|| (4 == argc && !ft_strncmp(argv[1], "J", 1)))
	{
		fractal.name = argv[1];
		fractal.julia_re = ft_atof(argv[2]);
		fractal.julia_im = ft_atof(argv[3]);
		ft_fractal_init(&fractal);
		ft_fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol [M/J] [/re] [/im]\n", 2);
		exit(1);
	}
	return (0);
}
