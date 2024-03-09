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

void	zoom(t_fractal *f, int x, int y, int direction)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	if (direction == SCROLL_UP)
		zoom_factor = 1.1;
	else
		zoom_factor = 0.9;
	mouse_re = (double)x / WIDTH * (f->max_r - f->min_r) + f->min_r;
	mouse_im = (double)y / HEIGHT * (f->max_i - f->min_i) + f->min_i;
	f->min_r = mouse_re + (f->min_r - mouse_re) * zoom_factor;
	f->max_r = mouse_re + (f->max_r - mouse_re) * zoom_factor;
	f->min_i = mouse_im + (f->min_i - mouse_im) * zoom_factor;
	f->max_i = mouse_im + (f->max_i - mouse_im) * zoom_factor;
}
