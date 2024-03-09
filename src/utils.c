/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:06:28 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 13:06:31 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

int	close_window(void *params)
{
	(void)params;
	exit(0);
}

void	clean_all(t_fractal *fractal)
{
	if (fractal->img)
		mlx_destroy_image(fractal->mlx, fractal->img);
	if (fractal->win && fractal->mlx)
		mlx_destroy_window(fractal->mlx, fractal->win);
	if (fractal->mlx)
		free(fractal->mlx);
}