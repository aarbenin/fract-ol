#include "../include/fractol.h"


int	mandelbrot_set(double x, double y, int max_iterations)
{
	double	zx;
	double	zy;
	int		n;
	double	tmp;

	zx = 0;
	zy = 0;
	n = 0;
	while (zx * zx + zy * zy < 4 && n < max_iterations)
	{
		tmp = zx * zx - zy * zy + x;
		zy = 2 * zx * zy + y;
		zx = tmp;
		n++;
	}
	return (n);
}

/*
int	mandelbrot_set(double x, double y, int max_iterations)
{
    // Преобразование координат в комплексное число
    double zx = 0;
    double zy = 0;
    double qx = (x - 0.25) * (x - 0.25) + y * y;
    // Проверка принадлежности к кардиоиде или периоду-2 
    if ((qx * (qx + (x - 0.25)) < 0.25 * y * y) || ((x + 1) * (x + 1) + y * y < 1 / 16.0)) {
        return max_iterations; // Точка принадлежит множеству Мандельброта
    }

    int n = 0;
    double tmp;
    while (zx * zx + zy * zy < 4 && n < max_iterations)
    {
        tmp = zx * zx - zy * zy + x;
        zy = 2 * zx * zy + y;
        zx = tmp;
        n++;
    }
    return n;
}
*/


void	set_pixel(t_fractal *fract, int x, int y, int color)
{
	int	pixel_pos;

	pixel_pos = (y * fract->line_length) + (x * (fract->bits_per_pixel / 8));
	*(unsigned int *)(fract->addr + pixel_pos) = color;
}

void	draw_fractal(t_fractal *fract, t_func color_func)
{
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
			//x = ((double)px / WIDTH) * (fract->max_r - fract->min_r) + fract->min_r;
			//y = ((double)py / HEIGHT) * (fract->max_i - fract->min_i) + fract->min_i;
 			x = ((double)px / WIDTH) * (fract->max_r - fract->min_r) + fract->min_r + fract->offset_x;
            y = ((double)py / HEIGHT) * (fract->max_i - fract->min_i) + fract->min_i + fract->offset_y;

			iterations = mandelbrot_set(x, y, fract->max_iterations);
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

/*
	double	base_shift;
	base_shift = 0.05;
	//shift_amount = base_shift / fractal->zoom;
	shift_amount = base_shift / log2(fractal->zoom + 1); //выбрать, какая глаже
	//shift_amount = base_shift / log(fractal->zoom + 1) / log(10);
*/
	shift_amount = (fractal->max_r - fractal->min_r) * 0.05;

	

    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(fractal->mlx, fractal->win);
        exit(0);
    }
	else if (keycode == KEY_LEFT)
    {
        fractal->offset_x -= shift_amount;
    }
    else if (keycode == KEY_RIGHT)
    {
        fractal->offset_x += shift_amount;
    }
    else if (keycode == KEY_UP)
    {
        fractal->offset_y -= shift_amount;
    }
    else if (keycode == KEY_DOWN)
    {
        fractal->offset_y += shift_amount;
    }


	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, get_unicorn_color);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		/*
		mlx_destroy_image(fract->mlx, fract->img);
        zoom(fract, x, y, button);
        fract->img = mlx_new_image(fract->mlx, WIDTH, HEIGHT);
        fract->addr = mlx_get_data_addr(fract->img, &fract->bits_per_pixel, &fract->line_length, &fract->endian);
        draw_fractal(fract, get_unicorn_color);
        mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
		*/
		zoom(fractal, x, y, button); // Применение масштабирования
    	draw_fractal(fractal, get_unicorn_color); // Перерисовка фрактала
 	   	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	
	return (0);
}



int	main(void)
{
	t_fractal fractal;

	fractal.mlx = mlx_init();
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Hello world!");
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bits_per_pixel, &fractal.line_length, &fractal.endian);
	init_mandelbrot(&fractal);
	
    mlx_hook(fractal.win, 17, 0, close_window, NULL);
    mlx_hook(fractal.win, 2, 1L<<0, handle_keypress, &fractal);
	mlx_hook(fractal.win, 4, 1L<<2, handle_mouse, &fractal);
   
    draw_fractal(&fractal, get_unicorn_color);

	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_loop(fractal.mlx);
   
}
