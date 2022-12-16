/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:42:01 by absaid            #+#    #+#             */
/*   Updated: 2022/12/16 10:55:49 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if((p2.x <= 1500 && p2.x > 0) && (p1.x < 1500 && p1.x > 0)
				&& (p2.y > 0 && p2.y <= 1000) && (p1.y > 0 && p1.y < 1000))
					my_mlx_pixel_put(data,p1.x, p1.y, p1.c);
			p1.y += dy / fabs(dx);
			p1.x += dx / fabs(dx);
		}
	}
	else
	{
		while( ++i <= fabs(dy))
		{
			if((p2.x <= 1500 && p2.x >= 0) && (p1.x <= 1500 && p1.x >= 0)
				&& (p2.y >= 0 && p2.y <= 1000) && (p1.y >= 0 && p1.y <= 1000))
					my_mlx_pixel_put(data,p1.x, p1.y, p1.c);
			p1.x += dx / fabs(dy);
			p1.y += dy / fabs(dy);
		}
	}
}

void update(t_point *p,t_data *ptr, t_point (*f)(t_point, t_data *ptr))
{
	int dw;
	int dm;
	int dist;

	dw = sqrt(pow(1500, 2) + pow(1000, 2));
	dm = sqrt(pow(ptr->xup , 2) + pow(ptr->yup , 2));
	dist = ((dw * 30) / 100) / (dm) ;
	if (dist < 2 && !ptr->zoom)
		dist = 2;
	p->x *= (dist + ptr->zoom);
	p->y *= (dist + ptr->zoom);
	p->x -= (ptr->xup * dist) / 2;
	p->y -= (ptr->yup * dist) / 2;
	// p->z += ptr->nz;
	*p = f(*p, ptr);

	p->x += 750 ;
	p->y += 500 ;
}

int key_press(int key, t_data *data)
{
	if(key == 53)
		exit(0);
	else if(key == 116 )
		data->rz += 0.05;
	else if(key == 121 )
		data->rz -= 0.05;
	else if(key == 15 )
	{
		fdf(data->coord,data,iso);
		data->sx = 0;
		data->sy = 0;
		data->zoom = 0;
	}
	else if(key == 34 )
	{
		data->rz = 0;	
		data->rx = 0;	
		data->ry = 0;
		data->sx = 0;
		data->sy = 0;
		data->zoom = 0;
			
	}
	else if(key == 126 )
		data->rx += 0.05;
	else if(key == 125 )
		data->rx -= 0.05;
	else if(key == 124 )
		data->ry += 0.05;
	else if(key == 123 )
		data->ry -= 0.05;
	else if(key == 1 )
		data->sy += 10;
	else if(key == 13 )
		data->sy -= 10;
	else if(key == 13 )
		data->sy -= 10;
	else if(key == 0 )
		data->sx -= 10;
	else if(key == 2 )
		data->sx += 10;
	else if(key == 78 )
		data->zoom -= 10;
	else if(key == 69 )
		data->nz += 10;
	
	mlx_destroy_image(data->mlx,data->img);
	data->img = mlx_new_image(data->mlx,1500,1000);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ln, &data->en);
	fdf(data->coord,data,rot);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	
	return 0;
}
int ft_exit(t_data *data)
{
	(void)data;
	exit(0);
}

int main(int ac, char **av)
{

	t_data data;

	data.zoom = 1;
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
		data.yup = filelen(fd);
		fd = open(filename, O_RDONLY);
		data.coord = parsing(fd, data.yup, &data.xup);
		if(!data.coord)
			return (printf("wrong map"));

		data.sx = 0;
		data.sy = 0;
		data.img = mlx_new_image(data.mlx,1500,1000);
		data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ln, &data.en);
	
		fdf(data.coord,&data,iso);

		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

		mlx_key_hook(data.win, key_press, &data);

		mlx_hook(data.win, 17, 0, ft_exit, &data);


		mlx_loop(data.mlx);
	}
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
