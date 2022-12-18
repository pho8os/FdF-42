/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:42:01 by absaid            #+#    #+#             */
/*   Updated: 2022/12/18 14:45:28 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_data(t_data *data, int j)
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
	if (j == 1)
	{
		data->rz = 0.523599;
		data->rx = 0.523599;
		data->ry = -0.523599;
	}
}

int	key_press(int key, t_data *p)
{
	if (key == 53)
		exit(0);
	else if (key == 116)
		p->rz += 0.05;
	else if (key == 121)
		p->rz -= 0.05;
	else if (key == 15)
		init_data(p, 1);
	else if (key == 34)
		init_data(p, 0);
	else if (key == 126)
		p->rx += 0.05;
	else if (key == 125)
		p->rx -= 0.05;
	else if (key == 124)
		p->ry += 0.05;
	else if (key == 123)
		p->ry -= 0.05;
	mlx_destroy_image(p->mlx, p->img);
	p->img = mlx_new_image(p->mlx, 1500, 1000);
	p->add = mlx_get_data_addr(p->img, &p->bpp, &p->ln, &p->en);
	fdf(p->coord, p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	return (0);
}

int	keypress2(int key, t_data *p)
{
	if (key == 0)
		p->sx -= 50;
	else if (key == 1)
		p->sy += 50;
	else if (key == 13)
		p->sy -= 50;
	else if (key == 2)
		p->sx += 50;
	else if (key == 78)
		p->zoom -= 1;
	else if (key == 69)
		p->zoom += 1;
	else if (key == 6)
		p->nz += 1;
	else if (key == 7)
		p->nz -= 1;
	else if (key == 8)
		p->nc += 1;
	key_press(key, p);
	mlx_destroy_image(p->mlx, p->img);
	p->img = mlx_new_image(p->mlx, 1500, 1000);
	p->add = mlx_get_data_addr(p->img, &p->bpp, &p->ln, &p->en);
	fdf(p->coord, p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	return (0);
}

int	ft_exit(void)
{
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac == 2)
	{
		data.mlx = mlx_init();
		init_data(&data, 1);
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
		fdf(data.coord, &data);
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_hook(data.win, 2, 1L << 0, keypress2, &data);
		mlx_hook(data.win, 17, 0, ft_exit, &data);
		mlx_loop(data.mlx);
	}
}
