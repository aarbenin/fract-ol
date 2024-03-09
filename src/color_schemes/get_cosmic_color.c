/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cosmic_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:50:04 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/09 11:50:11 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fractol.h"

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
		red = (int)(9 * (1 - r) * r * r * r * 255);
		green = (int)(15 * (1 - r) * (1 - r) * r * r * 255);
		blue = (int)(8.5 * (1 - r) * (1 - r) * (1 - r) * r * 255);
		color = (red << 16) | (green << 8) | blue;
	}
	else
		color = 0x000000;
	return (color);
}
