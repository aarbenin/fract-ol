/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:57:51 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 12:57:54 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

static int	is_valid_float(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_julia_params(int argc, char **argv, t_fractal *fractal)
{
	if (argc == 4)
	{
		if (is_valid_float(argv[2]) && is_valid_float(argv[3]))
		{
			fractal->julia_real = ft_atof(argv[2]);
			fractal->julia_imag = ft_atof(argv[3]);
		}
		else
		{
			ft_putendl_fd("Error: Invalid format for Julia set parameters", 2);
			ft_putstr_fd("Use only integers ", 2);
			ft_putendl_fd("or floating-point numbers as parameters", 2);
			print_julia_usage();
			exit (EXIT_FAILURE);
		}
	}
	else if (argc == 2)
		print_julia_default();
	else
	{
		ft_putendl_fd("Error: Incorrect number of parameters for Julia set", 2);
		print_julia_usage();
		exit (EXIT_FAILURE);
	}
}

void	parse_arguments(int argc, char **argv, t_fractal *fractal)
{
	fractal->type = INVALID;
	if (argc < 2 || argc > 4)
	{
		ft_putendl_fd("Error: Incorrect number of arguments", 2);
		print_usage();
		exit (EXIT_FAILURE);
	}
	init_fractal(fractal, argv);
	if (fractal->type == JULIA)
		handle_julia_params(argc, argv, fractal);
	else if (argc != 2)
	{
		ft_putendl_fd("Error: Only Julia set accepts additional parameters", 2);
		print_usage();
		exit (EXIT_FAILURE);
	}
	if (fractal->type == INVALID)
	{
		ft_putendl_fd("Error: Invalid fractal name", 2);
		print_usage();
		exit (EXIT_FAILURE);
	}
}
