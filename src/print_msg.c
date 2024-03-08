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
	ft_printf("Usage: ./fractol [fractal]\n");
	ft_printf("Available fractals:\n");
	ft_printf("  - mandelbrot\n");
	ft_printf("  - julia\n");
	ft_printf("  - ship (for burning ship)\n");
}

void	print_julia_usage(void)
{
	ft_printf("\nThe Julia set requires two additional parameters in either of the following formats:\n");
	ft_printf("	./fractol julia <real_part> <imaginary_part>\n");
	ft_printf("	./fractol julia \"<real_part>\" \"<imaginary_part>\"\n\n");
	ft_printf("Examples:\n");
	ft_printf("	./fractol julia -0.8 0.156\n");
	ft_printf("	./fractol julia \"-0.8\" \"0.156\"\n\n");
	ft_printf("For generating the Julia set with default parameters, run ./fractol julia\n\n");
}
void	print_julia_default(void)
{
	ft_printf("\nA Julia set was generated using default parameters\n");
	ft_printf("For custom parameters run: ./fractol julia <real_part> <imaginary_part>\n");
	ft_printf("The recommended range for both parameters is from -2 to 2.\n\n");
	ft_printf("You can also adjust parameters in real-time using the WASD keys:\n");
	ft_printf("	W = \"+\", S = \"-\" for imaginary part\n	A = \"+\", D = \"-\" for real part\n");
}