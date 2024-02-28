#include "../include/fractol.h"
#include <string.h>



int	mandelbrot_set(double x, double y, t_fractal *fract)
{
	double	zx;
	double	zy;
	double	qx;
	int		n;
	double	tmp;

	zx = 0;
	zy = 0;
	qx = (x - 0.25) * (x - 0.25) + y * y;
	if ((qx * (qx + (x - 0.25)) < 0.25 * y * y) || ((x + 1) * (x + 1) + y * y < 1 / 16.0))
        return fract->max_iterations; //  принадлежит множеству Мандельброта
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
	int		n;
	double	tmp;

	zx = x;
	zy = y;
	n = 0;
	while (zx * zx + zy * zy < 4 && n < fract->max_iterations)
	{
		tmp = zx * zx - zy * zy + fract->julia_real;
		zy = 2 * zx * zy + fract->julia_imag;
		zx = tmp;
		n++;
	}
	return (n);
}

int burning_ship_set(double x, double y, t_fractal *fract)
{
    double zx;
    double zy;
    double tmp;
    int n;

	zx = 0;
	zy = 0;
	n = 0;
    while (zx * zx + zy * zy < 4 && n < fract->max_iterations)
    {
        tmp = zx * zx - zy * zy + x;
        zy = fabs(2 * zx * zy) + y;
        zx = tmp;
        n++;
    }
    return n;
}


void	set_pixel(t_fractal *fract, int x, int y, int color)
{
	int	pixel_pos;

	pixel_pos = (y * fract->line_length) + (x * (fract->bits_per_pixel / 8));
	*(unsigned int *)(fract->addr + pixel_pos) = color;
}
t_color_func switch_scheme(int *current_scheme)
{
	int				number_of_schemes; 
	t_color_func	color_functions[5];
	t_color_func	selected;

	color_functions[0] = get_unicorn_color;
	color_functions[1] = get_cosmic_color;
	color_functions[2] = get_dark_color;
	color_functions[3] = get_zebra_color;
	color_functions[4] = get_fire_color;
	number_of_schemes = sizeof(color_functions) / sizeof(color_functions[0]);
	selected = color_functions[*current_scheme];
	*current_scheme = (*current_scheme + 1) % number_of_schemes;
	return (selected);
}
void	draw_fractal(t_fractal *fract, t_color_func color_func)
{
	(void)color_func;
	int		px;
	int		py;
	int		iterations;
	double	x;
	double	y;

	px = 0;
	py = 0;
	while (px < WIDTH)
	{
		while (py < HEIGHT)
		{
 			x = ((double)px / WIDTH) * (fract->max_r - fract->min_r) + fract->min_r + fract->offset_x;
            y = ((double)py / HEIGHT) * (fract->max_i - fract->min_i) + fract->min_i + fract->offset_y;

			iterations = fract->fractal_func(x, y, fract);
			fract->color = color_func(iterations, fract->max_iterations);
			set_pixel(fract, px, py, fract->color);
			py++;
		}
		py = 0;
		px++;
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
	fractal->max_iterations = 60;
	fractal->current_scheme = 0;
	fractal->color_func = &get_unicorn_color;
	fractal->fractal_func = &mandelbrot_set;
	
}
void	init_julia(t_fractal *fractal)
{
	fractal->type = JULIA;
	fractal->julia_real = -0.8;
	fractal->julia_imag = -0.2;
	fractal->min_r = -2.0; 
    fractal->max_r = 2.0;
    fractal->min_i = -2.0;
    fractal->max_i = 2.0;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 500;
	fractal->color_func = &get_cosmic_color;
	fractal->fractal_func = &julia_set;

}
void init_burning_ship(t_fractal *fractal)
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
	fractal->color_func = &get_fire_color;
    fractal->fractal_func = &burning_ship_set;
}


int	close_window(void *params)
{
	(void)params;
	exit(0);
}

void	zoom(t_fractal *fract, int x, int y, int direction)
{
	double	mouse_re;
	double	mouse_im;
	double	interpolation;
	double	zoom_factor;

	zoom_factor = 1.1;
	if (direction == SCROLL_UP)
	{
		interpolation = zoom_factor;
		fract->max_iterations += 20;
		if (fract->max_iterations > 1000)
			fract->max_iterations = 1000;
	}
		
	else
	{
		interpolation = 1 / zoom_factor;
		fract->max_iterations -= 20;
		if (fract->max_iterations < 60)
        fract->max_iterations = 60;
	}
		

	mouse_re = (double)x / WIDTH * (fract->max_r - fract->min_r) + fract->min_r;
	mouse_im = (double)y / HEIGHT * (fract->max_i - fract->min_i) + fract->min_i;

	fract->min_r = mouse_re + (fract->min_r - mouse_re) * interpolation;
    fract->max_r = mouse_re + (fract->max_r - mouse_re) * interpolation;
    fract->min_i = mouse_im + (fract->min_i - mouse_im) * interpolation;
    fract->max_i = mouse_im + (fract->max_i - mouse_im) * interpolation;

}


int handle_keypress(int keycode, t_fractal *fractal)
{
	double	shift_amount;

	shift_amount = (fractal->max_r - fractal->min_r) * 0.05;
	if (keycode == KEY_ESC)
    {
        mlx_destroy_window(fractal->mlx, fractal->win);
        exit(0);
    }
	else if (keycode == KEY_LEFT)
        fractal->offset_x -= shift_amount;
    else if (keycode == KEY_RIGHT)
        fractal->offset_x += shift_amount;
    else if (keycode == KEY_UP)
        fractal->offset_y -= shift_amount;
    else if (keycode == KEY_DOWN)
        fractal->offset_y += shift_amount;
	else if (keycode == KEY_W)
	{
		fractal->julia_imag += 0.05;
		printf("julia_imag: %f\n", fractal->julia_imag);
	}
	else if (keycode == KEY_S)
	{
		fractal->julia_imag -= 0.05;
		printf("julia_imag: %f\n", fractal->julia_imag);
	}
	else if (keycode == KEY_A)
	{
		fractal->julia_real -= 0.05;
		printf("julia_real: %f\n", fractal->julia_real);
	}
	else if (keycode == KEY_D)
	{
		fractal->julia_real += 0.05;
		printf("julia_real: %f\n", fractal->julia_real);
	}
	else if (keycode == KEY_SPACE)
	{
		fractal->current_scheme = (fractal->current_scheme + 1) % 5;
		fractal->color_func = switch_scheme(&fractal->current_scheme);	
	}
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->color_func);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		
		zoom(fractal, x, y, button);
    	draw_fractal(fractal, fractal->color_func);
 	   	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	
	return (0);
}



int	main(int argc, char **argv)
{
	t_fractal fractal;

	if (argc < 2)
	{
		ft_printf("Error message here...\n");
		exit(1);
	}
	
	
	fractal.mlx = mlx_init();
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Hello world!");
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bits_per_pixel, &fractal.line_length, &fractal.endian);
	
	if (strcmp(argv[1], "mandelbrot") == 0) //create ft_strcmp
	{
		init_mandelbrot(&fractal);
	}
	else if (strcmp(argv[1], "julia") == 0)
	{
		init_julia(&fractal);
	}
	else if (strcmp(argv[1], "burning_ship") == 0)
	{
		init_burning_ship(&fractal);
	}
	else
	{
		ft_printf("some error message here\n");
		exit(1);
	}
	
    mlx_hook(fractal.win, 17, 0, close_window, NULL);
    mlx_hook(fractal.win, 2, 1L<<0, handle_keypress, &fractal);
	mlx_hook(fractal.win, 4, 1L<<2, handle_mouse, &fractal);
   
    draw_fractal(&fractal, fractal.color_func);

	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_loop(fractal.mlx);
   
}
