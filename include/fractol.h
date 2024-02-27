#ifndef FRACTOL_H
#define FRACTOL_H

#define HEIGHT 1200
#define WIDTH 1200
#define MAX_ITERATIONS 60

// Key codes
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// Mouse codes
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define MOUSE_MIDDLE_BTN 3
# define MOUSE_RIGHT_BTN 1
# define MOUSE_LEFT_BTN 2


// event codes
# define EVENT_CLOSE_BTN 17


typedef int (*t_func)(int, int);


typedef enum e_fractal_type
{
    MANDELBROT,
    JULIA,
    
} t_fractal_type;

typedef struct s_fractal 
{
    t_fractal_type type;
    void   *mlx;
    void   *win;
    void   *img;
    char   *addr;
    int    bits_per_pixel;
    int    line_length;
    int    endian;
    int    color;
    int    max_iterations;
    double zoom;
    double offset_x;
    double offset_y;
    double max_r;
    double min_r;
    double max_i;
    double min_i;

    double  julia_real;
    double  julia_imag;

    int (*color_func)(int, int);
   
}   t_fractal;



# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"


int	get_unicorn_color(int iterations, int max_iterations);
int	get_cosmic_color(int iterations, int max_iterations);
int get_dark_color(int iterations, int max_iterations);
int get_zebra_color(int iterations, int max_iterations);





#endif
