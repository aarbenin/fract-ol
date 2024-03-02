#include "../include/fractol.h"

int	get_unicorn_color(int iterations, int max_iterations)
{
	double	frequency;
	int		red;
	int		green;
	int		blue;

	if (iterations == max_iterations)
		return (0x000000);
	else
	{
		frequency = 0.5;
		red = (int)(sin(frequency * iterations + 0) * 60 + 195);
		green = (int)(sin(frequency * iterations + 2) * 60 + 195);
		blue = (int)(sin(frequency * iterations + 4) * 60 + 195);
		return ((red << 16) | (green << 8) | blue);
	}
}

int	get_cosmic_color(int iterations, int max_iterations)
{
	int		color;
	double	t;
	int		red;
	int		green;
	int		blue;

	color = 0;
	t = (double)iterations / max_iterations;
	// Цвета: черный в центре, переходящий в жёлтый и белый на границах,на фоне синего
	if (iterations < max_iterations)
	{
		// Интерполяция между черным и желтым
		red = (int)(9 * (1 - t) * t * t * t * 255);
		green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		color = (red << 16) | (green << 8) | blue;
	}
	else
		color = 0x000000;
	
	return (color);
}


int get_zebra_color(int iterations, int max_iterations) 
{	
	double	value;

    if (iterations == max_iterations)
        return 0x000000; 
    // Используем синусоидальную функцию от числа итераций для создания эффекта зебры
    value = sin(iterations * 3); // плотность полос (красиво 3 и 0.8)
    // Если синус положительный, возвращаем белый цвет, иначе - черный
    if (value > 0)
        return 0xFFFFFF; 
    else
        return 0x000000;
}

int get_dark_color(int iterations, int max_iterations)
{
    double	normalized;
	int		red_intensity;

	if (iterations == max_iterations)
        return 0x000000; 
    normalized = (double)iterations / max_iterations;
    red_intensity = (int)(normalized * 255);
    return (red_intensity << 16) | (0 << 8) | 0;
}

int get_fire_color(int iterations, int max_iterations)
{
    double	ratio;
	int		red;
	int		blue;
	int		green;

	if (iterations == max_iterations)
        return 0x000000; 
    ratio = (double)iterations / max_iterations;

    
    red = (int)(255 * pow(ratio, 0.3));
    green = (int)(255 * pow(ratio, 0.5));
    blue = (int)(100 * pow(ratio, 0.7));

   
    if (red > 255)
		red = 255; 
    if (blue > 255)
		blue = 255;
	if (green > 255)
		green = 255;

	if (red < 100)
		red = 100;
	if (green < 50)
		green = 50;
    return (red << 16) | (green << 8) | blue;
}

/*
int get_fractal_color(int iterations, int max_iterations) //oгонь
{
   if (iterations == max_iterations) {
        return 0x000000; // Черный для точек внутри множества
    }
    
    const int colors[] = {0x070707, 0xFF4500, 0xFFD700, 0xFFFFF0}; // Черный, Оранжевый, Желтый, Белый
    double ratio = (double)iterations / max_iterations;
    int color_index = ratio * (sizeof(colors)/sizeof(colors[0]) - 1);
    double color_ratio = fmod(ratio * (sizeof(colors)/sizeof(colors[0]) - 1), 1.0);
    
    int start_color = colors[color_index];
    int end_color = colors[color_index + 1];
    
    // Разбиение цветов на компоненты
    int r_start = (start_color >> 16) & 0xFF;
    int g_start = (start_color >> 8) & 0xFF;
    int b_start = start_color & 0xFF;
    
    int r_end = (end_color >> 16) & 0xFF;
    int g_end = (end_color >> 8) & 0xFF;
    int b_end = end_color & 0xFF;
    
    // Интерполяция между значениями компонентов начального и конечного цвета
    int r = r_start + (r_end - r_start) * color_ratio;
    int g = g_start + (g_end - g_start) * color_ratio;
    int b = b_start + (b_end - b_start) * color_ratio;
    
    return (r << 16) | (g << 8) | b;
}

*/

int get_fractal_color(int iterations, int max_iterations) //julia
{
	double frequency;
    int red, green, blue;

    if (iterations == max_iterations) {
        return 0x000000; // Черный для точек внутри множества
    } else {
        frequency = 0.3; // Уменьшенная частота для более плавного перехода

        // Создаем плавные переходы цвета, используя sin и частоту
        red = (int)((sin(frequency * iterations + 0) * 127) + 128); // От темно-синего к светлому
        green = (int)((sin(frequency * iterations + 2) * 127) + 128); // Добавляем немного зеленого для холодного оттенка
        blue = (int)((sin(frequency * iterations + 4) * 127) + 128); // Основной синий цвет

        // Использование sin создает эффект морозного узора
        return (red << 16) | (green << 8) | blue;
    }
}


