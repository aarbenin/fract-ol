/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sunset_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:50:45 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/09 11:50:50 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fractol.h"

int	get_sunset_color(int iterations, int max_iterations)
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
