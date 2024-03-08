/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:55:14 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 12:55:23 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

t_color_func	switch_scheme(int *current_scheme)
{
	int				number_of_schemes;
	t_color_func	color_functions[6];
	t_color_func	selected;

	color_functions[0] = get_unicorn_color;
	color_functions[1] = get_cosmic_color;
	color_functions[2] = get_dark_color;
	color_functions[3] = get_zebra_color;
	color_functions[4] = get_fire_color;
	color_functions[5] = get_neon_color;
	number_of_schemes = sizeof(color_functions) / sizeof(color_functions[0]);
	selected = color_functions[*current_scheme];
	*current_scheme = (*current_scheme + 1) % number_of_schemes;
	return (selected);
}

void	init_fractal(t_fractal *fractal, char **argv)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0 || ft_strcmp(argv[1], "m") == 0)
		init_mandelbrot(fractal);
	else if (ft_strcmp(argv[1], "julia") == 0 || ft_strcmp(argv[1], "j") == 0)
		init_julia(fractal);
	else if (ft_strcmp(argv[1], "ship") == 0 || ft_strcmp(argv[1], "bs") == 0)
		init_burning_ship(fractal);
	else
		fractal->type = INVALID;
}


int	main(int argc, char **argv)
{
	t_fractal	fractal;

	fractal.mlx = mlx_init();
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Hello world!");
	parse_arguments(argc, argv, &fractal);
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bits_per_pixel, \
									&fractal.line_length, &fractal.endian);
	mlx_hook(fractal.win, 17, 0, close_window, NULL);
	mlx_hook(fractal.win, 2, 1L << 0, handle_keypress, &fractal);
	mlx_hook(fractal.win, 4, 1L << 2, handle_mouse, &fractal);
	draw_fractal(&fractal, fractal.color_func);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_loop(fractal.mlx);
}
