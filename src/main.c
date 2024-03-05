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

void	set_pixel(t_fractal *fract, int x, int y, int color)
{
	int				pixel_pos;
	unsigned int	*pixel_addr;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_pos = (y * fract->line_length) + (x << 2); // Эквивалентно (x * 4) для bits_per_pixel = 32
		pixel_addr = (unsigned int *)(fract->addr + pixel_pos);
		*pixel_addr = color;
	}
}

t_color_func	switch_scheme(int *current_scheme)
{
	int				number_of_schemes;
	t_color_func	color_functions[7];
	t_color_func	selected;

	color_functions[0] = get_unicorn_color;
	color_functions[1] = get_cosmic_color;
	color_functions[2] = get_dark_color;
	color_functions[3] = get_zebra_color;
	color_functions[4] = get_fire_color;
	color_functions[5] = get_neon_color;
	color_functions[6] = get_grey_color;
	number_of_schemes = sizeof(color_functions) / sizeof(color_functions[0]);
	selected = color_functions[*current_scheme];
	*current_scheme = (*current_scheme + 1) % number_of_schemes;
	return (selected);
}

void	draw_fractal(t_fractal *fract, t_color_func color_func)
{
	t_point	point;
	double	scale_x;
	double	scale_y;
	int		iterations;

	scale_x = (fract->max_r - fract->min_r) / WIDTH;
	scale_y = (fract->max_i - fract->min_i) / HEIGHT;
	point.px = 0;
	while (point.px < WIDTH)
	{
		point.py = 0;
		while (point.py < HEIGHT)
		{
			point.x = point.px * scale_x + fract->min_r + fract->offset_x;
			point.y = point.py * scale_y + fract->min_i + fract->offset_y;
			iterations = fract->fractal_func(point.x, point.y, fract);
			fract->color = color_func(iterations, fract->max_iterations);
			set_pixel(fract, point.px, point.py, fract->color);
			point.py++;
		}
		point.px++;
	}
}

void	init_mandelbrot(t_fractal *fractal)
{
	fractal->type = MANDELBROT;
	fractal->min_r = -1.9;
	fractal->max_r = 0.6;
	fractal->min_i = -1.25;
	fractal->max_i = 1.25;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 100;
	fractal->current_scheme = 0;
	fractal->color_func = &get_neon_color;
	fractal->fractal_func = &mandelbrot_set;
	fractal->scale_depth = 0;
}

void	init_julia(t_fractal *fractal)
{
	fractal->type = JULIA;
	fractal->julia_real = -0.8;
	fractal->julia_imag = -0.2;
	fractal->min_r = -2.0;
	fractal->max_r = 2.0;
	fractal->min_i = -2.0;
	fractal->max_i = 2.0;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 150;
	fractal->color_func = &get_cosmic_color;
	fractal->fractal_func = &julia_set;
	fractal->scale_depth = 0;
}

void	init_burning_ship(t_fractal *fractal)
{
	fractal->type = BURNING_SHIP;
	fractal->min_r = -2.0;
	fractal->max_r = -1.7;
	fractal->min_i = -0.1;
	fractal->max_i = 0.1;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.13;
	fractal->offset_y = -0.035;
	fractal->max_iterations = 100;
	fractal->color_func = &get_fire_color;
	fractal->fractal_func = &burning_ship_set;
	fractal->scale_depth = 0;
}

int	close_window(void *params)
{
	(void)params;
	exit(0);
}


void	handle_movement(t_fractal *fractal, int keycode, double shift_amount)
{
	if (keycode == KEY_LEFT)
		fractal->offset_x -= shift_amount;
	else if (keycode == KEY_RIGHT)
		fractal->offset_x += shift_amount;
	else if (keycode == KEY_UP)
		fractal->offset_y -= shift_amount;
	else if (keycode == KEY_DOWN)
		fractal->offset_y += shift_amount;
}

void	handle_iterations(t_fractal *fractal, int keycode)
{
	if (keycode == KEY_1)
	{
		fractal->max_iterations -= 10;
		ft_printf("max_iterations: %d\n", fractal->max_iterations);
	}
	else if (keycode == KEY_2)
	{
		fractal->max_iterations += 10;
		if (fractal->max_iterations < 0)
			fractal->max_iterations = 0;
		ft_printf("max_iterations: %d\n", fractal->max_iterations);
	}
}

void	handle_color_scheme(t_fractal *fractal, int keycode)
{
	if (keycode == KEY_SPACE)
	{
		fractal->current_scheme = (fractal->current_scheme) % 6;
		fractal->color_func = switch_scheme(&fractal->current_scheme);
	}
}

void	handle_julia(t_fractal *fractal, int keycode)
{
	if (keycode == KEY_W)
	{
		fractal->julia_imag += 0.05;
		printf("julia_imag: %f\n", fractal->julia_imag);
	}
	else if (keycode == KEY_S)
	{
		fractal->julia_imag -= 0.05;
		printf("julia_imag: %f\n", fractal->julia_imag);
	}
	else if (keycode == KEY_A)
	{
		fractal->julia_real -= 0.05;
		printf("julia_real: %f\n", fractal->julia_real);
	}
	else if (keycode == KEY_D)
	{
		fractal->julia_real += 0.05;
		printf("julia_real: %f\n", fractal->julia_real);
	}
}

int	handle_keypress(int keycode, t_fractal *fractal)
{
	double	shift_amount;

	shift_amount = (fractal->max_r - fractal->min_r) * 0.05;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		exit(0);
	}
	handle_movement(fractal, keycode, shift_amount);
	handle_julia(fractal, keycode);
	handle_iterations(fractal, keycode);
	handle_color_scheme(fractal, keycode);
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->color_func);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		zoom(fractal, x, y, button);
		draw_fractal(fractal, fractal->color_func);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	return (0);
}
//_________parameters_____________//

static void	init_fractal(t_fractal *fractal, char **argv)
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

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [fractal]\n");
	ft_printf("Available fractals:\n");
	ft_printf("  - mandelbrot\n");
	ft_printf("  - julia\n");
	ft_printf("  - ship (for burning ship)\n");
}

void	print_julia_usage(void)
{
	ft_printf("\nThe Julia set requires two additional parameters in either of the following formats:\n");
	ft_printf("	./fractol julia <real_part> <imaginary_part>\n");
	ft_printf("	./fractol julia \"<real_part>\" \"<imaginary_part>\"\n\n");
	ft_printf("Examples:\n");
	ft_printf("	./fractol julia -0.8 0.156\n");
	ft_printf("	./fractol julia \"-0.8\" \"0.156\"\n\n");
	ft_printf("For generating the Julia set with default parameters, run ./fractol julia\n\n");
}

int	is_valid_float(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_julia_params(int argc, char **argv, t_fractal *fractal)
{
	if (argc < 2)
	{
		print_usage();
		exit(1);
	}
	if (argc == 4 && is_valid_float(argv[2]) && is_valid_float(argv[3]))
	{
		fractal->julia_real = ft_atof(argv[2]);
		fractal->julia_imag = ft_atof(argv[3]);
	}
	else if (argc == 2)
	{
		ft_printf("\nA Julia set was generated using default parameters\n");
		printf("For custom parameters run: ./fractol julia <real_part> <imaginary_part>\n");
		ft_printf("The recommended range for both parameters is from -2 to 2.\n\n");
		ft_printf("You can also adjust parameters in real-time using the WASD keys:\n");
		ft_printf("	W = \"+\", S = \"-\" for imaginary part\n	A = \"+\", D = \"-\" for real part\n");
	}
	else
	{
		ft_printf("Error: invalid parameters\n");
		print_julia_usage();
		exit (1);
	}
}

void	parse_arguments(int argc, char **argv, t_fractal *fractal)
{
	fractal->type = INVALID;
	if (argc < 2 || argc > 4)
	{
		print_usage();
		exit (1);
	}
	init_fractal(fractal, argv);
	if (fractal->type == JULIA)
		handle_julia_params(argc, argv, fractal);
	else if (argc != 2)
	{
		ft_printf("Error: Only Julia set accepts additional parameters.\n\n");
		print_usage();
		exit (1);
	}
	if (fractal->type == INVALID)
	{
		ft_printf("Error: '%s' is not a valid fractal name.\n\n", argv[1]);
		print_usage();
		exit (1);
	}
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
