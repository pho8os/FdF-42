#include "fdf.h"




void draw_line_(t_data *data, int x0, int y0, int x1, int y1)
{
	int dy, dx, incrE, incrNE, d, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
	d = 2 * dy - dx;
	incrE = 2 * dy;
	incrNE = 2 * (dy - dx);
	x = x0;
	y = y0;

	mlx_pixel_put(data->mlx, data->win, x, y, 0xff10fa);
	while (x < x1)
	{
		if (d <= 0)
		{
			d += incrE;
			x++;
		}
		else
		{
			d += incrNE;
			x++;
			y++;
		}
		mlx_pixel_put(data->mlx, data->win, x, y, 0xff10fa);
	}
}
int main()
{

	t_data data;

	data.mlx = mlx_init();
	data.w = 600;
	data.h = 600;
	data.win = mlx_new_window(data.mlx, data.w, data.h, "Awbx");

	t_point p1 = {5, 87,80};
	t_point p2 = {250, 300,10};
	// draw_line_(&data, p1.x, p1.y ,p2.x,p2.y);

	p1 = get_x_y(&p1);
	p2 = get_x_y(&p2);

	printf("%d--%d\n",p1.x,p1.y);
	printf("%d--%d",p2.x,p2.y);
	draw_line_(&data, p1.x , p1.y , p2.x , p2.y);

	 mlx_loop(data.mlx);
}
