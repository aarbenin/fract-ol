#include "../include/fractol.h"
#include <string.h>
//______________MATH________________//
// t_complex   complex_add(t_complex a, t_complex b)
// {
//     t_complex   result;

//     result.re = a.re + b.re;
//     result.im = a.im + b.im;
//     return (result);
// }

// t_complex   complex_square(t_complex a)
// {
//     t_complex   result;

//     result.re = a.re * a.re - a.im * a.im;
//     result.im = 2 * a.re * a.im;
//     return (result);
// }

// double  complex_abs(t_complex a)
// {
//     return (sqrt(a.re * a.re + a.im * a.im));
// }

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




// int	julia_set(double x, double y, t_fractal *fract)
// {
// 	double	zx;
// 	double	zy;
// 	int		n;
// 	double	tmp;

// 	zx = x;
// 	zy = y;
// 	n = 0;
// 	while (zx * zx + zy * zy < 4 && n < fract->max_iterations)
// 	{
// 		tmp = zx * zx - zy * zy + fract->julia_real;
// 		zy = 2 * zx * zy + fract->julia_imag;
// 		zx = tmp;
// 		n++;
// 	}
// 	return (n);
// }
int julia_set(double x, double y, t_fractal *fract)
{
	double zx = x;
	double zy = y;
	int n = 0;

    // Предварительное вычисление квадратов zx и zy
	double zx2 = zx * zx;
	double zy2 = zy * zy;

	while (zx2 + zy2 < 4 && n < fract->max_iterations)
	{
		// Используем заранее вычисленные квадраты
		zy = 2 * zx * zy + fract->julia_imag;
		zx = zx2 - zy2 + fract->julia_real;

        // Обновляем квадраты для следующей итерации
		zx2 = zx * zx;
		zy2 = zy * zy;

		n++;
	}
	return n;
}

// int burning_ship_set(double x, double y, t_fractal *fract)
// {
//     double zx;
//     double zy;
//     double tmp;
//     int n;

// 	zx = 0;
// 	zy = 0;
// 	n = 0;
//     while (zx * zx + zy * zy < 4 && n < fract->max_iterations)
//     {
//         tmp = zx * zx - zy * zy + x;
//         zy = fabs(2 * zx * zy) + y;
//         zx = tmp;
//         n++;
//     }
//     return n;
// }
int burning_ship_set(double x, double y, t_fractal *fract)
{
    double zx = 0, zy = 0; // Начальные значения zx и zy
    int n = 0;
    double zx2 = 0, zy2 = 0; // Для хранения квадратов zx и zy

    while (zx2 + zy2 < 4 && n < fract->max_iterations)
    {
        zy = fabs(2 * zx * zy) + y;
        zx = zx2 - zy2 + x; // Используем предварительно вычисленные квадраты

        zx2 = zx * zx; // Обновляем квадраты
        zy2 = zy * zy;

        n++;
    }
    return n;
}


// void	set_pixel(t_fractal *fract, int x, int y, int color)
// {
// 	int	pixel_pos;

// 	pixel_pos = (y * fract->line_length) + (x * (fract->bits_per_pixel / 8));
// 	*(unsigned int *)(fract->addr + pixel_pos) = color;
// }

void	set_pixel(t_fractal *fract, int x, int y, int color)
{
	int	pixel_pos;
	unsigned int *pixel_addr;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) 
	{
		pixel_pos = (y * fract->line_length) + (x << 2); // Эквивалентно (x * 4) для bits_per_pixel = 32
		pixel_addr = (unsigned int *)(fract->addr + pixel_pos);
		*pixel_addr = color;

	}

}
t_color_func switch_scheme(int *current_scheme)
{
	int				number_of_schemes; 
	t_color_func	color_functions[6];
	t_color_func	selected;

	color_functions[0] = get_unicorn_color;
	color_functions[1] = get_cosmic_color;
	color_functions[2] = get_dark_color;
	color_functions[3] = get_zebra_color;
	color_functions[4] = get_fire_color;
	color_functions[5] = get_fractal_color;
	number_of_schemes = sizeof(color_functions) / sizeof(color_functions[0]);
	selected = color_functions[*current_scheme];
	*current_scheme = (*current_scheme + 1) % number_of_schemes;
	return (selected);
}
// void	draw_fractal(t_fractal *fract, t_color_func color_func)
// {
// 	(void)color_func;
// 	int		px;
// 	int		py;
// 	int		iterations;
// 	double	x;
// 	double	y;

// 	px = 0;
// 	py = 0;
// 	while (px < WIDTH)
// 	{
// 		while (py < HEIGHT)
// 		{
//  			x = ((double)px / WIDTH) * (fract->max_r - fract->min_r) + fract->min_r + fract->offset_x;
//             y = ((double)py / HEIGHT) * (fract->max_i - fract->min_i) + fract->min_i + fract->offset_y;

// 			iterations = fract->fractal_func(x, y, fract);
// 			fract->color = color_func(iterations, fract->max_iterations);
// 			set_pixel(fract, px, py, fract->color);
// 			py++;
// 		}
// 		py = 0;
// 		px++;
// 	}
// }

void	draw_fractal(t_fractal *fract, t_color_func color_func)
{
	int		px;
	int		py;
	double	scaleX = (fract->max_r - fract->min_r) / WIDTH;
	double	scaleY = (fract->max_i - fract->min_i) / HEIGHT;

	px = 0;
	while (px < WIDTH)
	{
		py = 0;
		while (py < HEIGHT)
		{
 			double x = px * scaleX + fract->min_r + fract->offset_x;
            double y = py * scaleY + fract->min_i + fract->offset_y;

			int iterations = fract->fractal_func(x, y, fract);
			fract->color = color_func(iterations, fract->max_iterations);
			set_pixel(fract, px, py, fract->color);
			py++;
		}
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
	fractal->color_func = &get_fractal_color;
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
/*
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
*/


void zoom(t_fractal *fract, int x, int y, int direction)
{
    double	zoom_actor;
    double	mouse_re; 
	double	mouse_im;

    // Установка zoom_actor в зависимости от направления
    if (direction == SCROLL_UP) {
        zoom_actor = 1.1;
    } else {
        zoom_actor = 0.9;
    }

    // Расчет координат мыши в комплексной плоскости
    mouse_re = (double)x / WIDTH * (fract->max_r - fract->min_r) + fract->min_r;
    mouse_im = (double)y / HEIGHT * (fract->max_i - fract->min_i) + fract->min_i;

    // Применение масштабирования
    fract->min_r = mouse_re + (fract->min_r - mouse_re) * zoom_actor;
    fract->max_r = mouse_re + (fract->max_r - mouse_re) * zoom_actor;
    fract->min_i = mouse_im + (fract->min_i - mouse_im) * zoom_actor;
    fract->max_i = mouse_im + (fract->max_i - mouse_im) * zoom_actor;

    // Адаптация количества итераций в зависимости от направления
    if (direction == SCROLL_UP) //уменьшение!!!!!
	{
		fract->max_iterations -= 5;
        if (fract->max_iterations < 60) 
            fract->max_iterations = 60;
        
        
		printf("iterations: %d\n", fract->max_iterations);
    } else {
        fract->max_iterations += 10;
        if (fract->max_iterations > 500) 
            fract->max_iterations = 500;
        
		printf("iterations: %d\n", fract->max_iterations);
    }
}







int handle_keypress(int keycode, t_fractal *fractal)
{
	printf("keycode: %d\n", keycode);
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
		fractal->current_scheme = (fractal->current_scheme) % 6;
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
//_________parameters_____________//


static void init_fractal (t_fractal *fractal, char **argv)
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

void print_usage(void)
{
    ft_printf("Usage: ./fractol [fractal]\n");
    ft_printf("Available fractals:\n");
    ft_printf("  - mandelbrot or m\n");
    ft_printf("  - julia or j\n");
    ft_printf("  - ship or s (for burning ship)\n");
}
int	str_is_num(char *str)
{
	while (*str)
	{
		if(!ft_isdigit(str))
			return (0);
		str++;
	}
	return (1);
}
static void handle_julia_params(int argc, char **argv, t_fractal *fractal)
{
    if (argc == 4 && str_is_num(argv[2] && str_is_num(argv[3])))
    {
        fractal->julia_real = ft_atof(argv[2]);
        fractal->julia_imag = ft_atof(argv[3]);
    }
	else if (argc == 2)
	{
		ft_printf("A Julia set was generated using default parameters\n");
		printf("For custom parameters run: ./fractol julia <real_part> <imaginary_part>\n");
		ft_printf("You can also adjust parameters in real-time using the WASD keys.\n");
	}
	else
	{
		ft_printf("Error: Julia set requires two additional parameters: <real_part> <imaginary_part>\n\n");
		print_usage();
    	exit (1);
	}
    	
}



void parse_arguments(int argc, char **argv, t_fractal *fractal)
{
	fractal->type = INVALID;
	if (argc < 2 || argc > 4) 
	{
        print_usage();
        exit (1);
    }
	init_fractal(fractal, argv);
	if (fractal->type == JULIA)
    {
        handle_julia_params(argc, argv, fractal);
    }
	else if (fractal->type == INVALID)
    {
        ft_printf("Error: '%s' is not a valid fractal name.\n\n", argv[1]);
        print_usage();
        exit (1);
    }
    
}

int	main(int argc, char **argv)
{
	t_fractal fractal;


	fractal.mlx = mlx_init();
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Hello world!");
	
	parse_arguments(argc, argv, &fractal);
	
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bits_per_pixel, &fractal.line_length, &fractal.endian);
	
	
    mlx_hook(fractal.win, 17, 0, close_window, NULL);
    mlx_hook(fractal.win, 2, 1L<<0, handle_keypress, &fractal);
	mlx_hook(fractal.win, 4, 1L<<2, handle_mouse, &fractal);
   
    draw_fractal(&fractal, fractal.color_func);

	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_loop(fractal.mlx);
   
}
