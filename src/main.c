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

int	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
	{
		ft_putendl_fd("Error initializing MLX", 2);
		return (0);
	}
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "fract-ol");
	if (!fractal->win)
	{
		ft_putendl_fd("Error creating window", 2);
		clean_mlx(fractal);
		return (0);
	}
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		ft_putendl_fd("Error creating image", 2);
		clean_mlx(fractal);
		return (0);
	}
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel, \
									&fractal->line_length, &fractal->endian);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	if (init_mlx(&fractal))
		parse_arguments(argc, argv, &fractal);
	mlx_hook(fractal.win, 17, 0, close_window, &fractal);
	mlx_hook(fractal.win, 2, 1L << 0, handle_keypress, &fractal);
	mlx_hook(fractal.win, 4, 1L << 2, handle_mouse, &fractal);
	draw_fractal(&fractal, fractal.color_func);
	print_controls();
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_loop(fractal.mlx);
	clean_mlx(&fractal);
	return (0);
}
