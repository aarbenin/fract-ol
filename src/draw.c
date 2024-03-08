/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:11:53 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 13:11:56 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

static void	set_pixel(t_fractal *fract, int x, int y, int color)
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
