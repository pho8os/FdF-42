#include "fdf.h"

void draw_line_(t_data *data, t_point p1, t_point p2)
{
	t_draw base;

	base.dx = abs(p2.x - p1.x);
	base.dy = -abs(p2.y - p1.y);
	base.sx = 1 - 2 * (p1.x > p2.x);
	base.sy = 1 - 2 * (p1.y > p2.y);
	base.d1 = base.dx + base.dy;
	base.d2 = 0;

	while (1)
	{
		if ((p1.x > 0 && p1.x < data->w) && (p1.y > 0 && p1.y < data->h))
			mlx_pixel_put(data->mlx, data->win, p1.x, p1.y, p1.c);
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		base.d2 = 2 * base.d1;
		if (base.d2 >= base.dy)
		{
			// if (x0 == x1)
			// 	break;
			base.d1 += base.dy;
			p1.x += base.sx;
		}
		if (base.d2 <= base.dx)
		{
			// if (y0 == y1)
			// 	break;
			base.d1 += base.dx;
			p1.y += base.sy;
		}
		if (p1.c > p2.c)
			p1.c -= 10;
		if (p1.c < p2.c)
			p1.c += 10;
	}
}
void  center(t_point *p)
{
	p->x += 750;
	p->y += 500;
	
}
void update(t_point *p, int ***coord)
{
	int dw;
	int i;
	int j;
	int dm;
	int dist;
	i = -1;
	while (coord[++i])
	{
		j = -1;
		while (coord[i][++j])
			;
	}
	dw = round(sqrt(pow(1500, 2) + pow(1000, 2)));
	dm = round(sqrt(pow(j, 2) + pow(i, 2)));
	dist = round(((dw * 30) / 100) / dm);
	if (dist < 2)
		dist = 2;
	p->x *= dist;
	p->y *= dist;
	p->x -= (j * dist) / 2;
	p->y -= (i * dist) / 2;
}
int main(int ac, char **av)
{

	t_data data;

	data.mlx = mlx_init();
	data.w = 1500;
	data.h = 1000;
	data.win = mlx_new_window(data.mlx, data.w, data.h, "phobos");
	if (ac > 1)
	{
		char *filename = av[1];
		int fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (fprintf(stderr, "%s\n", strerror(errno)), 1);
		t_map *cords = parsing(fd);
		int ***coord = get_coords(cords);
		int i = -1, j;
		while (coord[++i])
		{
			j = -1;
			while (coord[i][++j])
			{
				t_point p1, p2, p3;
				p1.x = j;
				p1.y = i;
				p1.c = coord[i][j][1];
				p1.z = coord[i][j][0];

				p2.x = j + 1;
				p2.y = i;
				if (coord[i][j + 1])
				{
					p2.c = coord[i][j + 1][1];
					p2.z = coord[i][j + 1][0];
				}

				p3.x = j;
				p3.y = i + 1;
				if (coord[i + 1])
				{
					p3.c = coord[i + 1][j][1];
					p3.z = coord[i + 1][j][0];
				}
				update(&p1, coord);
				update(&p2, coord);
				update(&p3, coord);
				p1 = iso(p1);
				p2 = iso(p2);
				p3 = iso(p3);
				center(&p1);
				center(&p2);
				center(&p3);
				if (coord[i][j + 1])
					draw_line_(&data, p1, p2);
				if (coord[i + 1])
					draw_line_(&data, p1, p3);
			}
		}
	}

	mlx_loop(data.mlx);
}
