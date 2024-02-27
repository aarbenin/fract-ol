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
    if (iterations == max_iterations)
        return 0x000000; // Черный цвет для точек, не убегающих в бесконечность

    // Используем синусоидальную функцию от числа итераций для создания эффекта зебры
    double value = sin(iterations * 3); // плотность полос (красиво 3 и 0.8)

    // Если синус положительный, возвращаем белый цвет, иначе - черный
    if (value > 0)
        return 0xFFFFFF; // Белый цвет
    else
        return 0x000000; // Черный цвет
}

int get_dark_color(int iterations, int max_iterations)
{
    if (iterations == max_iterations)
        return 0x000000; // Черный цвет для точек внутри множества

    // Нормализуем количество итераций для получения значения интенсивности
    double normalized = (double)iterations / max_iterations;
    
    // Преобразуем нормализованное значение в интенсивность красного цвета (0 - 255)
    int red_intensity = (int)(normalized * 255);

    // Возвращаем оттенок красного с полной интенсивностью красного и нулевыми значениями для зеленого и синего
    return (red_intensity << 16) | (0 << 8) | 0;
}