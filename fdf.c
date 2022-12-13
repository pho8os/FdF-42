/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 00:57:33 by absaid            #+#    #+#             */
/*   Updated: 2022/12/13 11:31:07 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"
void init_ptr(t_fdf *ptr)
{
	ptr->p1  = malloc(sizeof(t_point));
	ptr->p2  = malloc(sizeof(t_point));
	ptr->p3  = malloc(sizeof(t_point));
}
void init_coord(t_point *p, int x, int y, int **candz)
{
	p->x = x;
	p->y = y;
	if(candz && candz[x])
	{
		p->c = candz[x][1];
		p->z = candz[x][0];
	}
	
}

void fdf(int ***coord, t_data *data, int xup, int yup)
{
	t_fdf ptr;
	
	init_ptr(&ptr);
	ptr.y = -1;
	while (coord[++ptr.y])
	{
		ptr.x = -1;
		while (coord[ptr.y][++ptr.x])
		{
			
			init_coord(ptr.p1, ptr.x, ptr.y, coord[ptr.y]);
			init_coord(ptr.p2, (ptr.x + 1), ptr.y, coord[ptr.y]);
			init_coord(ptr.p3, ptr.x, (ptr.y + 1), coord[(ptr.y + 1)]);
			update(ptr.p1, yup,xup,1);
			update(ptr.p2, yup,xup,1);
			update(ptr.p3, yup,xup,1);
			if (coord[ptr.y][ptr.x + 1])
				draw_line_(data, *ptr.p1, *ptr.p2);
			if (coord[ptr.y + 1])
				draw_line_(data, *ptr.p1, *ptr.p3);
		}
	}
	free(ptr.p1);
	free(ptr.p2);
	free(ptr.p3);

}
	