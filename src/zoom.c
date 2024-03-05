/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:11:00 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 14:11:03 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

static int	calc_iterations(double scale_depth)
{
	return ((int)(BASE_ITERATIONS + scale_depth * ITERATIONS_STEP));
}

void	zoom(t_fractal *fract, int x, int y, int direction)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	if (direction == SCROLL_UP)
		zoom_factor = 1.15;
	else
		zoom_factor = 0.85;
// координаты мыши в комплексной плоскости
	mouse_re = (double)x / WIDTH * (fract->max_r - fract->min_r) + fract->min_r;
	mouse_im = (double)y / HEIGHT * (fract->max_i - fract->min_i) + fract->min_i;
// масштабирование
	fract->min_r = mouse_re + (fract->min_r - mouse_re) * zoom_factor;
	fract->max_r = mouse_re + (fract->max_r - mouse_re) * zoom_factor;
	fract->min_i = mouse_im + (fract->min_i - mouse_im) * zoom_factor;
	fract->max_i = mouse_im + (fract->max_i - mouse_im) * zoom_factor;
	if (direction == SCROLL_UP) //уменьшение!!!!!
	{
		fract->scale_depth -= 1;
		printf("scale: %f, iterations: %d\n", fract->scale_depth, fract->max_iterations);
	}
	else
	{
		fract->scale_depth += 1;
		printf("scale: %f, iterations: %d\n", fract->scale_depth, fract->max_iterations);
	}
	fract->max_iterations = calc_iterations(fract->scale_depth);
	if (fract->max_iterations > MAX_ITERATIONS)
		fract->max_iterations = MAX_ITERATIONS;
	if (fract->max_iterations < MIN_ITERATIONS)
		fract->max_iterations = MIN_ITERATIONS;
}