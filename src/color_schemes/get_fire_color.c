/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fire_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:48:57 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/09 11:49:01 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fractol.h"

static t_color	get_rgb_components(int color)
{
	t_color	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

static int	interpolate_color(int start_color, int end_color, double ratio)
{
	t_color	start;
	t_color	end;
	t_color	result;

	start = get_rgb_components(start_color);
	end = get_rgb_components(end_color);
	result.r = start.r + (int)((end.r - start.r) * ratio);
	result.g = start.g + (int)((end.g - start.g) * ratio);
	result.b = start.b + (int)((end.b - start.b) * ratio);
	return ((result.r << 16) | (result.g << 8) | result.b);
}

int	get_fire_color(int iterations, int max_iterations) //огонь
{
	int		color_count;
	double	ratio;
	int		color_index;
	double	color_ratio;
	int		colors[4];

	colors[0] = 0x070707;
	colors[1] = 0xFF4500;
	colors[2] = 0xFFD700;
	colors[3] = 0xFFFFF0;
	color_count = sizeof(colors) / sizeof(colors[0]);
	if (iterations == max_iterations)
		return (0x000000);
	ratio = (double)iterations / max_iterations;
	color_index = ratio * (color_count - 1);
	color_ratio = fmod(ratio * (color_count - 1), 1.0);
	return (interpolate_color(colors[color_index], colors[color_index + 1],
			color_ratio));
}
