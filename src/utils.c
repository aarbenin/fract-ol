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

int	close_window(t_fractal *fractal)
{
	clean_mlx(fractal);
	exit(0);
}

void	clean_mlx(t_fractal *fractal)
{
	if (!fractal)
		return ;
	if (fractal->img && fractal->mlx)
		mlx_destroy_image(fractal->mlx, fractal->img);
	if (fractal->win && fractal->mlx)
		mlx_destroy_window(fractal->mlx, fractal->win);
}

void	print_float(float f)
{
	long	l;

	if (f < 0)
	{
		f = -f;
		write(1, "-", 1);
	}
	l = (long)f;
	ft_putnbr_fd(l, 1);
	write(1, ".", 1);
	f -= (float)l;
	l = f * 100000;
	if (l % 10 >= 5)
		l = l / 10 + 1;
	else
		l /= 10;
	if (l < 1000)
		ft_putstr_fd("0", 1);
	else if (l < 100)
		ft_putstr_fd("0", 1);
	else if (l < 10)
		ft_putstr_fd("0", 1);
	ft_putnbr_fd(l, 1);
}
