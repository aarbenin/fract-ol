/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:58:34 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 12:58:38 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

static void	adjust_view(t_fractal *fractal)
{
	double	range_i;
	double	center_i;

	range_i = (fractal->max_r - fractal->min_r) * HEIGHT / WIDTH;
	center_i = (fractal->max_i + fractal->min_i) / 2;
	fractal->min_i = center_i - range_i / 2;
	fractal->max_i = center_i + range_i / 2;
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
	fractal->color_func = &get_unicorn_color;
	fractal->fractal_func = &mandelbrot_set;
	adjust_view(fractal);
}

void	init_julia(t_fractal *fractal)
{
	fractal->type = JULIA;
	fractal->julia_real = -0.8;
	fractal->julia_imag = -0.185;
	fractal->min_r = -2.0;
	fractal->max_r = 2.0;
	fractal->min_i = -2.0;
	fractal->max_i = 2.0;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 300;
	fractal->color_func = &get_cosmic_color;
	fractal->fractal_func = &julia_set;
	adjust_view(fractal);
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
	fractal->color_func = &get_sunset_color;
	fractal->fractal_func = &burning_ship_set;
	adjust_view(fractal);
}
