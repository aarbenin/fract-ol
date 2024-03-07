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
	int red;
    int green;
    int blue;

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
		// Интерполяция между черным и желтым
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
	// Если синус положительный, возвращаем белый цвет, иначе - черный
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

int get_fire_color(int iterations, int max_iterations) 
{
    if (iterations == max_iterations) 
        return 0x000000; 

    double ratio = (double)iterations / max_iterations;
 
    int red = (int)(255 * pow(ratio, 0.4));
    int green = (int)(255 * pow(ratio, 0.6));
    // Добавляем больше красного и зеленого для усиления "огненного" эффекта
    int blue = (int)(255 * pow(ratio, 0.8));

    // Убираем синий компонент, чтобы сделать цвета более теплыми
    blue = fmax(0, fmin(blue - 50, 255));

    red = fmin(red, 255);
    green = fmin(green, 255);

    // увеличить яркость и контрастность
    red = fmax(100, red);
    green = fmax(30, green);

    return (red << 16) | (green << 8) | blue;
}


//____________test______________//
static t_color	get_rgb_components(int color)
{
    t_color rgb;

    rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
    return (rgb);
}
static int	interpolate_color(int start_color, int end_color, double ratio)
{
    t_color start;
    t_color end;
    t_color result;

	start = get_rgb_components(start_color);
	end = get_rgb_components(end_color);
	result.r = start.r + (int)((end.r - start.r) * ratio);
	result.g = start.g + (int)((end.g - start.g) * ratio);
	result.b = start.b + (int)((end.b - start.b) * ratio);
	return ((result.r << 16) | (result.g << 8) | result.b);
}
int	get_dark_color(int iterations, int max_iterations) //огонь
{
	int		color_count;
	double	ratio;
	int		color_index;
	double	color_ratio;

	const int colors[] = {0x070707, 0xFF4500, 0xFFD700, 0xFFFFF0}; // Черный, Оранжевый, Желтый, Белый
	color_count = sizeof(colors) / sizeof(colors[0]);
	if (iterations == max_iterations)
		return (0x000000);
	ratio = (double)iterations / max_iterations;
	color_index = ratio * (color_count - 1);
	color_ratio = fmod(ratio * (color_count - 1), 1.0);
	return (interpolate_color(colors[color_index], colors[color_index + 1],
			color_ratio));
}

