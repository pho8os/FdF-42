/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:14:37 by absaid            #+#    #+#             */
/*   Updated: 2022/12/18 14:47:26 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

int	validpoint(t_point p1, t_point p2)
{
	if ((p2.x < 1500 && p2.x > 0) && (p1.x < 1500 && p1.x > 0)
		&& (p2.y > 0 && p2.y < 1000) && (p1.y > 0 && p1.y < 1000))
		return (1);
	return (0);
}

void	draw_line_(t_data *data, t_point p1, t_point p2)
{
	int	i;

	data->dx = p2.x - p1.x;
	data->dy = p2.y - p1.y;
	i = -1;
	if (fabs(data->dx) > fabs(data->dy))
	{
		while (++i <= fabs(data->dx))
		{
			if (validpoint(p1, p2))
				my_mlx_pixel_put(data, p1.x, p1.y, p1.c);
			p1.y += data->dy / fabs(data->dx);
			p1.x += data->dx / fabs(data->dx);
		}
	}
	else
	{
		while (++i <= fabs(data->dy))
		{
			if (validpoint(p1, p2))
				my_mlx_pixel_put(data, p1.x, p1.y, p1.c);
			p1.x += data->dx / fabs(data->dy);
			p1.y += data->dy / fabs(data->dy);
		}
	}
}

void	update(t_point *p, t_data *ptr)
{
	int	dw;
	int	dm;
	int	dist;

	dw = sqrt(pow(1500, 2) + pow(1000, 2));
	dm = sqrt(pow(ptr->xup, 2) + pow(ptr->yup, 2));
	dist = ((dw * 50) / 100) / dm;
	if (dist < 2 && !ptr->zoom)
		dist = 2;
	p->x *= (dist + ptr->zoom);
	p->y *= (dist + ptr->zoom);
	p->x -= (ptr->xup * dist) / 2;
	p->y -= (ptr->yup * dist) / 2;
	if (p->z)
		p->z *= ptr->nz;
	*p = rot(*p, ptr);
	p->x += 750 ;
	p->y += 500 ;
	p->c += ((0xaaaa + ptr->nc) * (ptr->nc * 10));
}
