/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_neon_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:48:13 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/09 11:48:23 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fractol.h"

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
