/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:11:45 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 14:11:49 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

static void	handle_movement(t_fractal *fractal, int keycode, double shift)
{
	if (keycode == KEY_LEFT)
		fractal->offset_x -= shift;
	else if (keycode == KEY_RIGHT)
		fractal->offset_x += shift;
	else if (keycode == KEY_UP)
		fractal->offset_y -= shift;
	else if (keycode == KEY_DOWN)
		fractal->offset_y += shift;
}

static void	handle_appearance(t_fractal *fractal, int keycode)
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
		fractal->julia_imag += 0.015;
		print_julia_fields("julia_imag", fractal->julia_imag);
	}
	else if (keycode == KEY_S)
	{
		fractal->julia_imag -= 0.015;
		print_julia_fields("julia_imag", fractal->julia_imag);
	}
	else if (keycode == KEY_A)
	{
		fractal->julia_real -= 0.015;
		print_julia_fields("julia_real", fractal->julia_real);
	}
	else if (keycode == KEY_D)
	{
		fractal->julia_real += 0.015;
		print_julia_fields("julia_real", fractal->julia_real);
	}
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

int	handle_keypress(int keycode, t_fractal *fractal)
{
	double	shift;

	shift = (fractal->max_r - fractal->min_r) * 0.05;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		exit(0);
	}
	handle_movement(fractal, keycode, shift);
	handle_julia(fractal, keycode);
	handle_appearance(fractal, keycode);
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->color_func);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}
