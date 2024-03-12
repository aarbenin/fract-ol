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

// event codes
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

int				get_unicorn_color(int iterations, int max_iterations);
int				get_cosmic_color(int iterations, int max_iterations);
int				get_sunset_color(int iterations, int max_iterations);
int				get_zebra_color(int iterations, int max_iterations);
int				get_fire_color(int iterations, int max_iterations);
int				get_neon_color(int iterations, int max_iterations);

t_color_func	switch_scheme(int *current_scheme);

//_________utils___________________//
int				close_window(void *params);
void			clean_mlx(t_fractal *fractal);
void			print_float(float f);

//____________sets_______________//
int				mandelbrot_set(double x, double y, t_fractal *fract);
int				julia_set(double x, double y, t_fractal *fract);
int				burning_ship_set(double x, double y, t_fractal *fract);

void			draw_fractal(t_fractal *fract, t_color_func color_func);

//__________inits_________________//
void			init_mandelbrot(t_fractal *fractal);
void			init_julia(t_fractal *fractal);
void			init_burning_ship(t_fractal *fractal);

void			init_fractal(t_fractal *fractal, char **argv);

//____________parameters_______________//
void			parse_arguments(int argc, char **argv, t_fractal *fractal);

void			zoom(t_fractal *fract, int x, int y, int direction);

//___________events___________________//
int				handle_mouse(int button, int x, int y, void *param);
int				handle_keypress(int keycode, t_fractal *fractal);

//_____________msg___________//
void			print_usage(void);
void			print_julia_usage(void);
void			print_julia_default(void);
void			print_julia_fields(char *field_name, double d);
void			print_controls(void);
#endif

#include "../include/fractol.h"

static void	set_pixel(t_fractal *fract, int x, int y, int color)
{
	int				pixel_pos;
	unsigned int	*pixel_addr;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_pos = (y * fract->line_length) + (x << 2);
		pixel_addr = (unsigned int *)(fract->addr + pixel_pos);
		*pixel_addr = color;
	}
}

void	draw_fractal(t_fractal *fract, t_color_func color_func)
{
	t_point	point;
	double	scale_x;
	double	scale_y;
	int		iterations;

	scale_x = (fract->max_r - fract->min_r) / WIDTH;
	scale_y = (fract->max_i - fract->min_i) / HEIGHT;
	point.px = 0;
	while (point.px < WIDTH)
	{
		point.py = 0;
		while (point.py < HEIGHT)
		{
			point.x = point.px * scale_x + fract->min_r + fract->offset_x;
			point.y = point.py * scale_y + fract->min_i + fract->offset_y;
			iterations = fract->fractal_func(point.x, point.y, fract);
			fract->color = color_func(iterations, fract->max_iterations);
			set_pixel(fract, point.px, point.py, fract->color);
			point.py++;
		}
		point.px++;
	}
}
static void	handle_movement(t_fractal *fractal, int keycode, double shift)
{
	if (keycode == KEY_LEFT)
		fractal->offset_x -= shift;
	else if (keycode == KEY_RIGHT)
		fractal->offset_x += shift;
	else if (keycode == KEY_UP)
		fractal->offset_y -= shift;
	else if (keycode == KEY_DOWN)
		fractal->offset_y += shift;
}

static void	handle_appearance(t_fractal *fractal, int keycode)
{
	if (keycode == KEY_1)
	{
		fractal->max_iterations -= 10;
		ft_printf("max_iterations: %d\n", fractal->max_iterations);
	}
	else if (keycode == KEY_2)
	{
		fractal->max_iterations += 10;
		if (fractal->max_iterations < 0)
			fractal->max_iterations = 0;
		ft_printf("max_iterations: %d\n", fractal->max_iterations);
	}
	if (keycode == KEY_SPACE)
	{
		fractal->current_scheme = (fractal->current_scheme) % 6;
		fractal->color_func = switch_scheme(&fractal->current_scheme);
	}
}

void	handle_julia(t_fractal *fractal, int keycode)
{
	if (keycode == KEY_W)
	{
		fractal->julia_imag += 0.015;
		print_julia_fields("julia_imag", fractal->julia_imag);
	}
	else if (keycode == KEY_S)
	{
		fractal->julia_imag -= 0.015;
		print_julia_fields("julia_imag", fractal->julia_imag);
	}
	else if (keycode == KEY_A)
	{
		fractal->julia_real -= 0.015;
		print_julia_fields("julia_real", fractal->julia_real);
	}
	else if (keycode == KEY_D)
	{
		fractal->julia_real += 0.015;
		print_julia_fields("julia_real", fractal->julia_real);
	}
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		zoom(fractal, x, y, button);
		draw_fractal(fractal, fractal->color_func);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	return (0);
}

int	handle_keypress(int keycode, t_fractal *fractal)
{
	double	shift;

	shift = (fractal->max_r - fractal->min_r) * 0.05;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		exit(0);
	}
	handle_movement(fractal, keycode, shift);
	handle_julia(fractal, keycode);
	handle_appearance(fractal, keycode);
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->color_func);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}
int	mandelbrot_set(double x, double y, t_fractal *fract)
{
	double	zx;
	double	zy;
	double	quick_check;
	int		n;
	double	tmp;

	zx = 0;
	zy = 0;
	quick_check = (x - 0.25) * (x - 0.25) + y * y;
	if ((quick_check * (quick_check + (x - 0.25)) < 0.25 * y * y) || \
	((x + 1) * (x + 1) + y * y < 1 / 16.0))
		return (fract->max_iterations);
	n = 0;
	while (zx * zx + zy * zy < 4 && n < fract->max_iterations)
	{
		tmp = zx * zx - zy * zy + x;
		zy = 2 * zx * zy + y;
		zx = tmp;
		n++;
	}
	return (n);
}

int	julia_set(double x, double y, t_fractal *fract)
{
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;
	int		n;

	zx = x;
	zy = y;
	n = 0;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (zx2 + zy2 < 4 && n < fract->max_iterations)
	{
		zy = 2 * zx * zy + fract->julia_imag;
		zx = zx2 - zy2 + fract->julia_real;
		zx2 = zx * zx;
		zy2 = zy * zy;
		n++;
	}
	return (n);
}

int	burning_ship_set(double x, double y, t_fractal *fract)
{
	int		n;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;

	zx = 0;
	zy = 0;
	zx2 = 0;
	zy2 = 0;
	n = 0;
	while (zx2 + zy2 < 4 && n < fract->max_iterations)
	{
		zy = fabs(2 * zx * zy) + y;
		zx = zx2 - zy2 + x;
		zx2 = zx * zx;
		zy2 = zy * zy;
		n++;
	}
	return (n);
}
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
void	init_mandelbrot(t_fractal *fractal)
{
	fractal->type = MANDELBROT;
	fractal->min_r = -1.9;
	fractal->max_r = 0.6;
	fractal->min_i = -1.25;
	fractal->max_i = 1.25;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 100;
	fractal->current_scheme = 0;
	fractal->color_func = &get_unicorn_color;
	fractal->fractal_func = &mandelbrot_set;
}

void	init_julia(t_fractal *fractal)
{
	fractal->type = JULIA;
	fractal->julia_real = -0.8;
	fractal->julia_imag = -0.185;
	fractal->min_r = -2.0;
	fractal->max_r = 2.0;
	fractal->min_i = -2.0;
	fractal->max_i = 2.0;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 300;
	fractal->color_func = &get_cosmic_color;
	fractal->fractal_func = &julia_set;
}

void	init_burning_ship(t_fractal *fractal)
{
	fractal->type = BURNING_SHIP;
	fractal->min_r = -2.0;
	fractal->max_r = -1.7;
	fractal->min_i = -0.1;
	fractal->max_i = 0.1;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.13;
	fractal->offset_y = -0.035;
	fractal->max_iterations = 100;
	fractal->color_func = &get_sunset_color;
	fractal->fractal_func = &burning_ship_set;
}
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

int	close_window(void *params)
{
	(void)params;
	exit(0);
}

void	clean_mlx(t_fractal *fractal)
{
	if (fractal->img)
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

void	zoom(t_fractal *f, int x, int y, int direction)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	if (direction == SCROLL_UP)
		zoom_factor = 1.1;
	else
		zoom_factor = 0.9;
	mouse_re = (double)x / WIDTH * (f->max_r - f->min_r) + f->min_r;
	mouse_im = (double)y / HEIGHT * (f->max_i - f->min_i) + f->min_i;
	f->min_r = mouse_re + (f->min_r - mouse_re) * zoom_factor;
	f->max_r = mouse_re + (f->max_r - mouse_re) * zoom_factor;
	f->min_i = mouse_im + (f->min_i - mouse_im) * zoom_factor;
	f->max_i = mouse_im + (f->max_i - mouse_im) * zoom_factor;
}
void	init_fractal(t_fractal *fractal, char **argv)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0 || ft_strcmp(argv[1], "m") == 0)
		init_mandelbrot(fractal);
	else if (ft_strcmp(argv[1], "julia") == 0 || ft_strcmp(argv[1], "j") == 0)
		init_julia(fractal);
	else if (ft_strcmp(argv[1], "ship") == 0 || ft_strcmp(argv[1], "bs") == 0)
		init_burning_ship(fractal);
	else
		fractal->type = INVALID;
}

int	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
	{
		ft_putendl_fd("Error initializing MLX", 2);
		return (0);
	}
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "fract-ol");
	if (!fractal->win)
	{
		ft_putendl_fd("Error creating window", 2);
		clean_mlx(fractal);
		return (0);
	}
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		ft_putendl_fd("Error creating image", 2);
		clean_mlx(fractal);
		return (0);
	}
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel, \
									&fractal->line_length, &fractal->endian);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	if (init_mlx(&fractal))
		parse_arguments(argc, argv, &fractal);
	mlx_hook(fractal.win, 17, 0, close_window, NULL);
	mlx_hook(fractal.win, 2, 1L << 0, handle_keypress, &fractal);
	mlx_hook(fractal.win, 4, 1L << 2, handle_mouse, &fractal);
	draw_fractal(&fractal, fractal.color_func);
	print_controls();
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_loop(fractal.mlx);
	clean_mlx(&fractal);
	return (0);
}