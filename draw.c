#include "fdf.h"

void draw_line_(t_data *data, t_point p1, t_point p2)
{
	double dx;
	double dy;
	int i;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	i = -1;
	if(fabs(dx) > fabs(dy))
	{
		while( ++i <= fabs(dx))
		{
			my_mlx_pixel_put(data,p1.x, p1.y, p1.c -= 2);
			p1.y += dy / fabs(dx);
			p1.x += dx / fabs(dx);
		}
	}
	else
	{
		while( ++i <= fabs(dy))
		{
			my_mlx_pixel_put(data,p1.x, p1.y, p1.c += 2);
			p1.x += dx / fabs(dy);
			p1.y += dy / fabs(dy);
		}
	}
}

void update(t_point *p, int y, int x, int flag)
{
	int dw;
	int dm;
	int dist;

	dw = sqrt(pow(1500, 2) + pow(1000, 2));
	dm = sqrt(pow(x, 2) + pow(y, 2));
	dist = ((dw * 50) / 100) / dm;
	if (dist < 2)
		dist = 2;
	p->x *= dist;
	p->y *= dist;
	p->x -= (x * dist) / 2;
	p->y -= (y * dist) / 2;
	if(flag == 1)
		*p = iso(*p);
	p->x += 750;
	p->y += 500;
}

int key_press(int key, t_data *data, int ***coord)
{
	(void)data;
	(void)coord;
	if(key == 53)
		exit(0);
	
	// if(key == 116 )
	// 	fdf(coord,data);
	// printf("%d\n",key);
	return 0;
}
int ft_exit(t_data *data)
{
	(void)data;
	exit(0);
}
int key_release(int key, t_data *data)
{
	(void)data;
	(void)key;
	// printf("%d\n",key);
	return 0;
}

int main(int ac, char **av)
{

	t_data data;

	data.mlx = mlx_init();
	data.w = 1500;
	data.h = 1000;
	data.win = mlx_new_window(data.mlx, data.w, data.h, "fdf");
	if (ac > 1)
	{
		char *filename = av[1];
		int fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (printf("wrong map"));
		int len = filelen(fd);
		fd = open(filename, O_RDONLY);
		int x;
		int ***coord = parsing(fd, len, &x);
		if(!coord)
			return (printf("wrong map"));
		
		data.img = mlx_new_image(data.mlx,1500,1000);
		data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ln, &data.en);
		fdf(coord,&data, x, len);
		// t_point p1,p2;
		// p1.x = 10;
		// p1.y = 10;
		// p1.c = 0xffffff;
		// p2.x = 100;
		// p2.y = 100;
		// p2.c = 0xffffff;
		
		// draw_line_(&data,p1,p2);
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	}
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, ft_exit, &data);
	// mlx_mouse_hook(data.win, 17, 0, mouse, &data);
	mlx_loop(data.mlx);
}
// 116 page up
// 121 page down
// 126 up
// 125 down
// 124 right
// 123 left
// 78 minus
// 69 plus
// 13 scale up
// 0 scale left
// 1 scale down 
// 2 scale right
// 4 zoom in
// 5 zoom out
