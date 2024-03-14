/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:59:50 by aarbenin          #+#    #+#             */
/*   Updated: 2024/03/05 12:59:54 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H

# define HEIGHT 1000
# define WIDTH 1000

// Key codes
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_SPACE 49
# define KEY_1 18
# define KEY_2 19

// Mouse codes
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define MOUSE_MIDDLE_BTN 3
# define MOUSE_RIGHT_BTN 1
# define MOUSE_LEFT_BTN 2

// Event codes
# define EVENT_CLOSE_BTN 17

# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct s_fractal	t_fractal;

typedef int					(*t_color_func)(int, int);
typedef int					(*t_fractal_func)(double x, double y, t_fractal *f);

typedef struct s_complex
{
	double		re;
	double		im;
}				t_complex;

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP,
	INVALID
}				t_fractal_type;

typedef struct s_fractal
{
	t_fractal_type	type;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				color;
	int				max_iterations;
	int				current_scheme;
	double			zoom;
	double			offset_x;
	double			offset_y;
	double			max_r;
	double			min_r;
	double			max_i;
	double			min_i;

	double			julia_real;
	double			julia_imag;

	int				(*color_func)(int, int);
	int				(*fractal_func)(double x, double y, t_fractal *fract);
}					t_fractal;

typedef struct s_point
{
	int		px;
	int		py;
	double	x;
	double	y;
}				t_point;

typedef struct s_rgb_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

// ========================= Color schemes =========================
int				get_unicorn_color(int iterations, int max_iterations);
int				get_cosmic_color(int iterations, int max_iterations);
int				get_sunset_color(int iterations, int max_iterations);
int				get_zebra_color(int iterations, int max_iterations);
int				get_fire_color(int iterations, int max_iterations);
int				get_neon_color(int iterations, int max_iterations);

t_color_func	switch_scheme(int *current_scheme);

// ========================= Utils =========================
void			clean_mlx(t_fractal *fractal);
void			print_float(float f);
int				close_window(t_fractal *fractal);

// ========================= Fractals =========================
int				mandelbrot_set(double x, double y, t_fractal *fract);
int				julia_set(double x, double y, t_fractal *fract);
int				burning_ship_set(double x, double y, t_fractal *fract);
void			draw_fractal(t_fractal *fract, t_color_func color_func);

// ========================= Initializations =========================
void			init_mandelbrot(t_fractal *fractal);
void			init_julia(t_fractal *fractal);
void			init_burning_ship(t_fractal *fractal);
void			init_fractal(t_fractal *fractal, char **argv);

// ========================= Parameters =========================
void			parse_arguments(int argc, char **argv, t_fractal *fractal);

// ========================= Events =========================
int				handle_mouse(int button, int x, int y, void *param);
int				handle_keypress(int keycode, t_fractal *fractal);
void			zoom(t_fractal *fract, int x, int y, int direction);

// ========================= Messages =========================
void			print_usage(void);
void			print_julia_usage(void);
void			print_julia_default(void);
void			print_julia_fields(char *field_name, double d);
void			print_controls(void);
#endif
