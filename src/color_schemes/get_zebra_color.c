/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_zebra_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:49:24 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/09 11:49:28 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fractol.h"

int	get_zebra_color(int iterations, int max_iterations)
{
	double	value;

	if (iterations == max_iterations)
		return (0x000000);
	value = sin(iterations * 3);
	if (value > 0)
		return (0xFFFFFF);
	else
		return (0x000000);
}
