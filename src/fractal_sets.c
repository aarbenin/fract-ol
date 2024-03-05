/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:57:30 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 12:57:32 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

int	mandelbrot_set(double x, double y, t_fractal *fract)
{
	double	zx;
	double	zy;
	double	qx;
	int		n;
	double	tmp;

	zx = 0;
	zy = 0;
	qx = (x - 0.25) * (x - 0.25) + y * y;
	if ((qx * (qx + (x - 0.25)) < 0.25 * y * y) || \
	((x + 1) * (x + 1) + y * y < 1 / 16.0))
		return (fract->max_iterations); //  принадлежит множеству Мандельброта
	n = 0;
	while (zx * zx + zy * zy < 4 && n < fract->max_iterations)
	{
		tmp = zx * zx - zy * zy + x;
		zy = 2 * zx * zy + y;
		zx = tmp;
		n++;
	}
	return (n);
}

int	julia_set(double x, double y, t_fractal *fract)
{
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;
	int		n;

	zx = x;
	zy = y;
	n = 0;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (zx2 + zy2 < 4 && n < fract->max_iterations)
	{
		zy = 2 * zx * zy + fract->julia_imag;
		zx = zx2 - zy2 + fract->julia_real;
		zx2 = zx * zx;
		zy2 = zy * zy;
		n++;
	}
	return (n);
}

int	burning_ship_set(double x, double y, t_fractal *fract)
{
	int		n;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;

	zx = 0;
	zy = 0;
	zx2 = 0;
	zy2 = 0;
	n = 0;
	while (zx2 + zy2 < 4 && n < fract->max_iterations)
	{
		zy = fabs(2 * zx * zy) + y;
		zx = zx2 - zy2 + x; // Используем предварительно вычисленные квадраты
		zx2 = zx * zx; // Обновляем квадраты
		zy2 = zy * zy;
		n++;
	}
	return (n);
}