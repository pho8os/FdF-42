/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 08:34:16 by absaid            #+#    #+#             */
/*   Updated: 2022/12/11 09:44:40 by absaid           ###   ########.fr       */
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
#include "get_next_line.h"
#include "lib-ft/libft.h"

typedef struct s_data
{
	void *mlx;
	void *win;
	int w, h;
} t_data;

typedef struct s_map
{
	int **coord;
	size_t len;
	struct s_map *next;
} t_map;

typedef struct s_pars
{
	char *line;
	t_map *head;
	t_map *initial;
	int len;
	int **coords;
} t_pars;

typedef struct s_point
{
	int x;
	int y;
	int z;
	int c;
} t_point;
typedef struct s_draw
{
	int dy;
	int dx;
	int d1;
	int d2;
	int sx;
	int sy;
} t_draw;

int	ft_mapsize(t_map *lst);
t_point rot_x(t_point p, double angle);
t_point rot_y(t_point p, double angle);
t_point rot_z(t_point p, double angle);
t_point	iso(t_point p);
int	ft_mapsize(t_map *lst);
int ***get_coords(t_map *lst);
t_map *parsing(int fd);
t_point  get_x_y(t_point *p1);
void draw_line_(t_data *data, t_point p1, t_point p2);
void	ft_mapclear(t_map **lst);
void map_push_back(t_map **head, int **coord, size_t len);
int hextodec(char *str);

#endif