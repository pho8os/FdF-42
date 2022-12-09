#include "fdf.h"

void draw_line_(t_data *data, int x0, int y0, int x1, int y1)
{
	t_draw base;

	base.dx = abs(x1 - x0);
	base.dy = -abs(y1 - y0);
	base.sx = 1 -  2 * (x0 > x1);
	base.sy = 1 - 2 * (y0 > y1);	
	base.d1 = base.dx + base.dy;
	base.d2 = 0;
	while (1)
	{
		if ((x0 > 0 && x0 < 600) && (y0 > 0 && y0 < 600))
			mlx_pixel_put(data->mlx, data->win, x0, y0, 0xff10fa);
		if (x0 == x1 && y0 == y1)
			break;
		base.d2 = 2 * base.d1;
		if(base.d2 >= base.dy)
		{
			// if (x0 == x1)
			// 	break;
			base.d1 += base.dy;
			x0 += base.sx;
		}
		if (base.d2 <= base.dx)
		{
			// if (y0 == y1)
			// 	break;
			base.d1 += base.dx;
			y0 += base.sy;
		}
	}
}
int	center(int a)
{

	return (a);
}

int main()
{

	t_data data;

	data.mlx = mlx_init();
	data.w = 1500;
	data.h = 1000;
	data.win = mlx_new_window(data.mlx, data.w, data.h, "phobos");

	draw_line_(&data, 10 , 90 ,100 , 90);
	draw_line_(&data, 100 , 90 ,100 , 180);
	draw_line_(&data, 10 , 180 ,100 , 180);
	draw_line_(&data, 10 , 180 ,10 , 90);
	// draw_line_(&data, 40 , 180 ,20 , 90);

	 mlx_loop(data.mlx);
}
