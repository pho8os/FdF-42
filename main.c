/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:42:01 by absaid            #+#    #+#             */
/*   Updated: 2022/12/18 12:13:33 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void init_data(t_data *data,int j)
{
	data->zoom = 0;
	data->w = 1500;
	data->h = 1000;
	data->sx = 0;
	data->sy = 0;
	data->nz = 1;
	data->nc = 0;
	data->rz = 0;
	data->rx = 0;
	data->ry = 0;
	if(j == 1)
	{
		data->rz = 0.523599;
		data->rx = 0.523599;
		data->ry = -0.523599;
	}
}

int key_press(int key, t_data *data)
{
	if(key == 53)
		exit(0);
	else if (key == 116 )
		data->rz += 0.05;
	else if (key == 121 )
		data->rz -= 0.05;
	else if (key == 15 )
		init_data(data,1);
	else if (key == 34 )
		init_data(data,0);
	else if(key == 126 )
		data->rx += 0.05;
	else if(key == 125 )
		data->rx -= 0.05;
	else if(key == 124 )
		data->ry += 0.05;
	else if(key == 123 )
		data->ry -= 0.05;
	mlx_destroy_image(data->mlx,data->img);
	data->img = mlx_new_image(data->mlx,1500,1000);
	data->add = mlx_get_data_addr(data->img, &data->bpp, &data->ln, &data->en);
	fdf(data->coord,data,rot);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return 0;
}
int keypress2(int key, t_data *data)
{
	if(key == 0 )
		data->sx -= 50;
	else if(key == 1 )
		data->sy += 50;
	else if(key == 13 )
		data->sy -= 50;
	else if(key == 2 )
		data->sx += 50;
	else if(key == 78 )
		data->zoom -= 1;
	else if(key == 69 )
		data->zoom += 1;
	else if(key == 6 )
		data->nz += 1;
	else if(key == 7)
		data->nz -= 1;
	else if(key == 8)
		data->nc += 1;
	key_press(key,data);
	mlx_destroy_image(data->mlx,data->img);
	data->img = mlx_new_image(data->mlx,1500,1000);
	data->add = mlx_get_data_addr(data->img, &data->bpp, &data->ln, &data->en);
	fdf(data->coord,data,rot);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return(0);
}

int ft_exit()
{
	exit(0);
}

int main(int ac, char **av)
{

	t_data	data;
	int fd;
	
	if (ac == 2)
	{
		data.mlx = mlx_init();
		init_data(&data,0);
		data.win = mlx_new_window(data.mlx, data.w, data.h, "fdf");
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			return (write(1, "file doesn't exist", 18));
		data.yup = filelen(fd); 
		fd = open(av[1], O_RDONLY);
		data.coord = parsing(fd, data.yup, &data.xup);
		if (!data.coord)
			return (write(1, "wrong map", 9));
		data.img = mlx_new_image(data.mlx, 1500, 1000);
		data.add = mlx_get_data_addr(data.img, &data.bpp, &data.ln, &data.en);
		fdf(data.coord, &data, iso);
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_hook(data.win, 2, 1L<<0, keypress2, &data);
		mlx_hook(data.win, 17, 0, ft_exit, &data);
		mlx_loop(data.mlx);
	}
}
