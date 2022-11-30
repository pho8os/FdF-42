#include "fdf.h"

typedef struct s_point
{
	int x;
	int y;
} t_point;

typedef struct s_data
{
	void *mlx;
	void *win;
	int w, h;
} t_data;

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

	// plot_point(x, y);
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

void draw_line(t_data *data, t_point *start, t_point *end)
{
	draw_line_(data, start->x, start->y, end->x, end->y);
}

int main()
{

	t_data data;

	data.mlx = mlx_init();
	data.w = 600;
	data.h = 600;
	data.win = mlx_new_window(data.mlx, data.w, data.h, "Awbx");

	t_point p1 = {0, 0};
	t_point p2 = {600, 0};
	int i = 1;
	while (i < data.w)
	{
		draw_line(&data, &p1, &p2);
		p1.y += 1;
		p2.y += 1;
		i++;
	}
	mlx_loop(data.mlx);
}