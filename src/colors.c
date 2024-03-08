/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:57:11 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 12:57:13 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	get_unicorn_color(int iterations, int max_iterations)
{
	float	frequency;
	int		red;
	int		green;
	int		blue;

	if (iterations == max_iterations)
		return (0x000000);
	else
	{
		frequency = 0.5;
		red = (int)(sin(frequency * iterations + 0) * 60 + 195);
		green = (int)(sin(frequency * iterations + 2) * 60 + 195);
		blue = (int)(sin(frequency * iterations + 4) * 60 + 195);
		return ((red << 16) | (green << 8) | blue);
	}
}

int	get_neon_color(int iterations, int max_iterations)
{
	float	frequency;
	int		red;
	int		green;
	int		blue;

	if (iterations == max_iterations)
	{
		return (0x000000);
	}
	else
	{
		frequency = 0.3;
		red = (int)((sin(frequency * iterations + 0) * 127) + 128);
		green = (int)((sin(frequency * iterations + 2) * 127) + 128);
		blue = (int)((sin(frequency * iterations + 4) * 127) + 128);
		return ((red << 16) | (green << 8) | blue);
	}
}

int	get_cosmic_color(int iterations, int max_iterations)
{
	int		color;
	double	r;
	int		red;
	int		green;
	int		blue;

	color = 0;
	r = (double)iterations / max_iterations;
	if (iterations < max_iterations)
	{
		//между черным и желтым
		red = (int)(9 * (1 - r) * r * r * r * 255);
		green = (int)(15 * (1 - r) * (1 - r) * r * r * 255);
		blue = (int)(8.5 * (1 - r) * (1 - r) * (1 - r) * r * 255);
		color = (red << 16) | (green << 8) | blue;
	}
	else
		color = 0x000000;
	return (color);
}

int	get_zebra_color(int iterations, int max_iterations)
{
	double	value;

	if (iterations == max_iterations)
		return (0x000000);
	value = sin(iterations * 3); // плотность полос (красиво 3 и 0.8)
	if (value > 0)
		return (0xFFFFFF);
	else
		return (0x000000);
}

// int	get_fire_color(int iterations, int max_iterations)
// {
// 	double	ratio;
// 	int		red;
// 	int		blue;
// 	int		green;

// 	if (iterations == max_iterations)
// 		return (0x000000);
// 	ratio = (double)iterations / max_iterations;
// 	red = (int)(255 * pow(ratio, 0.3));
// 	green = (int)(255 * pow(ratio, 0.5));
// 	blue = (int)(100 * pow(ratio, 0.7));
// 	if (red > 255)
// 		red = 255;
// 	if (blue > 255)
// 		blue = 255;
// 	if (green > 255)
// 		green = 255;
// 	if (red < 100)
// 		red = 100;
// 	if (green < 50)
// 		green = 50;
// 	return ((red << 16) | (green << 8) | blue);
// }

int	get_fire_color(int iterations, int max_iterations)
{
	double	ratio;
	t_color	rgb;

	if (iterations == max_iterations) 
		return (0x000000);
	ratio = (double)iterations / max_iterations;
	rgb.r = (int)(255 * pow(ratio, 0.3));
	rgb.g = (int)(255 * pow(ratio, 0.5));
	rgb.b = (int)(255 * pow(ratio, 0.7));
	rgb.b -= 50;
	if (rgb.b < 0)
		rgb.b = 0;
	if (rgb.b > 255)
		rgb.b = 50;
	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.r < 100)
		rgb.r = 100;
	if (rgb.g < 30)
		rgb.g = 30;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
