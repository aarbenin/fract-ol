/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:34:11 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/08 12:34:26 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	print_usage(void)
{
	ft_putendl_fd("Usage: ./fractol <fractal>", 1);
	ft_putendl_fd("Available fractals:", 1);
	ft_putendl_fd("  - mandelbrot", 1);
	ft_putendl_fd("  - julia", 1);
	ft_putendl_fd("  - ship (for burning ship)", 1);
}

void	print_julia_usage(void)
{
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("The Julia set requires two additional parameters ", 1);
	ft_putendl_fd("in either of the following formats:", 1);
	ft_putendl_fd("	./fractol julia <real_part> <imaginary_part>", 1);
	ft_putendl_fd("	./fractol julia \"<real_part>\" \"<imaginary_part>\"", 1);
	ft_putendl_fd("Examples:", 1);
	ft_putendl_fd("	./fractol julia -0.8 0.156", 1);
	ft_putendl_fd("	./fractol julia \"-0.8\" \"0.156\"", 1);
	ft_putstr_fd("For generating the Julia set with default parameters, ", 1);
	ft_putendl_fd("run ./fractol julia", 1);
	ft_putchar_fd('\n', 1);
}

void	print_julia_default(void)
{
	ft_putendl_fd("A Julia set was generated using default parameters", 1);
	ft_putstr_fd("For custom parameters run: ", 1);
	ft_putendl_fd("./fractol julia <real_part> <imaginary_part>", 1);
	ft_putstr_fd("The recommended range for both parameters ", 1);
	ft_putendl_fd("is from -2 to 2.", 1);
	ft_putstr_fd("You can also adjust parameters in ", 1);
	ft_putend_fd("real-time using the WASD keys:", 1);
	ft_putend_fd("	W = \"+\", S = \"-\" for imaginary part", 1);
	ft_putend_fd("	A = \"+\", D = \"-\" for real part", 1);

}
