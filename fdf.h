/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 08:34:16 by absaid            #+#    #+#             */
/*   Updated: 2022/11/30 17:36:57 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <mlx.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include "gnl/get_next_line.h"
#include "lib-ft/libft.h"

typedef struct s_data
{
	void *mlx;
	void *win;
	int w, h;
} t_data;

typedef struct s_point
{
	int x;
	int y;
	int z;
} t_point;

typedef struct s_map
{
	int **coord;
	size_t len;
	struct s_map *next;
} t_map;

t_point  get_x_y(t_point *p1);
void draw_line_(t_data *data, int x0, int y0, int x1, int y1);
void	ft_mapclear(t_map **lst);
void map_push_back(t_map **head, int **coord, size_t len);
int hextodec(char *str);

#endif