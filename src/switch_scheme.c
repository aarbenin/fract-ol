/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_scheme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:20:54 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/09 12:20:59 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

t_color_func	switch_scheme(int *current_scheme)
{
	int				number_of_schemes;
	t_color_func	color_functions[6];
	t_color_func	selected;

	color_functions[0] = get_unicorn_color;
	color_functions[1] = get_cosmic_color;
	color_functions[2] = get_sunset_color;
	color_functions[3] = get_zebra_color;
	color_functions[4] = get_fire_color;
	color_functions[5] = get_neon_color;
	number_of_schemes = sizeof(color_functions) / sizeof(color_functions[0]);
	selected = color_functions[*current_scheme];
	*current_scheme = (*current_scheme + 1) % number_of_schemes;
	return (selected);
}
