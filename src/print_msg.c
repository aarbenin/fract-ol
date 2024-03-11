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

void	print_controls(void)
{
	ft_putendl_fd("======================================================", 1);
	ft_putendl_fd("                       Controls:                      ", 1);
	ft_putendl_fd("======================================================", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("           [Arrow keys] - move around", 1);
	ft_putendl_fd("           [Mouse scroll] - zoom in/out", 1);
	ft_putendl_fd("           [1] - decrease max iterations", 1);
	ft_putendl_fd("           [2] - increase max iterations", 1);
	ft_putendl_fd("           [Space] - switch color scheme", 1);
	ft_putendl_fd("           [ESC] - exit the program", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("-> Julia set specific:", 1);
	ft_putendl_fd("           [W/A/S/D] - change parameters of Julia set", 1);
	ft_putendl_fd("______________________________________________________", 1);
}

void	print_usage(void)
{
	ft_putendl_fd("=======================================================", 1);
	ft_putendl_fd("                    Fract-ol usage:                    ", 1);
	ft_putendl_fd("=======================================================", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("   Syntax: ./fractol <fractal_name>", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("   <fractal_name can be one of the following:>:", 1);
	ft_putendl_fd("       - mandelbrot", 1);
	ft_putendl_fd("       - julia", 1);
	ft_putendl_fd("       - ship (for burning ship)", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("   Example:", 1);
	ft_putendl_fd("       ./fractol mandelbrot", 1);
	ft_putendl_fd("       ./fractol julia -0.4 0.6", 1);
	ft_putendl_fd("_______________________________________________________", 1);
}

void	print_julia_usage(void)
{
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("The Julia set requires two additional parameters ", 1);
	ft_putendl_fd("in either of the following formats:", 1);
	ft_putendl_fd("   ./fractol julia <real_part> <imaginary_part>", 1);
	ft_putendl_fd("   ./fractol julia \"<real_part>\" \"<imaginary_part>\"", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("-> For generating the Julia set with default parameters ", 1);
	ft_putendl_fd("run ./fractol julia", 1);
	ft_putchar_fd('\n', 1);
}

void	print_julia_default(void)
{
	ft_putendl_fd("A Julia set was generated using default parameters", 1);
	ft_putstr_fd("You can adjust parameters in ", 1);
	ft_putendl_fd("real-time using the WASD keys:", 1);
	ft_putendl_fd("           [W/S] - increase/decrease imaginary part", 1);
	ft_putendl_fd("           [A/D] - increase/decrease real part", 1);
	ft_putstr_fd("-> The recommended range for both parameters ", 1);
	ft_putendl_fd("is from -2 to 2.", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("-> For custom parameters run: ", 1);
	ft_putendl_fd("./fractol julia <real_part> <imaginary_part>", 1);
	ft_putchar_fd('\n', 1);
}

void	print_julia_fields(char *field_name, double d)
{
	ft_putstr_fd(field_name, 1);
	ft_putstr_fd(": ", 1);
	print_float(d);
	ft_putchar_fd('\n', 1);
}
