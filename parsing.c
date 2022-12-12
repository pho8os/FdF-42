/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:41:50 by absaid            #+#    #+#             */
/*   Updated: 2022/12/12 02:28:54 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>
#include <errno.h>

void	struct_init(t_pars *structo)
{
	(structo)->head = NULL;
	(structo)->initial = NULL;
}

int	*chartoint(char *str)
{
	char	**info;
	int		*ret;

	info = ft_split(str, ',');
	ret = ft_calloc(2, sizeof(int));
	ret[0] = ft_atoi(info[0]);
	ret[1] = 0xffffff;
	if (info[1])
	{
		ret[1] = hextodec(info[1]);
		if (ret[1] == 0)
			ret[1] = 0xffffff;
	}
	return (free(info[0]), free(info[1]), free(info), free(str), ret);
}

int	**line_to_cords(char *line, int *len)
{
	char	**points;
	int		**coords;
	int		i;

	i = -1;
	points = ft_split(line, 32);
	while (points[*len])
			(*len)++;
	coords = ft_calloc(*len + 1, sizeof(int *));
	while (++i < *len)
		coords[i] = chartoint(points[i]);
	free(points);
	return (coords);
}

t_map	*parsing(int fd)
{
	t_pars	ptr;

	struct_init(&ptr);
	ptr.line = get_next_line(fd);
	if (!ptr.line)
		return (NULL);
	while (ptr.line)
	{
		ptr.len = 0;
		ptr.coords = line_to_cords(ptr.line, &ptr.len);
		if (!ptr.initial && ptr.head)
			ptr.initial = ptr.head;
		if (ptr.initial && ptr.initial->len != (size_t)ptr.len)
			return (NULL);
		map_push_back(&ptr.head, ptr.coords, ptr.len);
		free(ptr.line);
		ptr.line = get_next_line(fd);
	}
	return (free(ptr.line), ptr.head);
}

int	***get_coords(t_map *lst)
{
	int		***coord;
	t_map	*tmp;
	int		i;
	int		len;

	if (!lst)
		return (NULL);
	tmp = lst;
	len = ft_mapsize(tmp);
	i = -1;
	tmp = lst;
	coord = ft_calloc(len + 1, sizeof(int *));
	if (!coord)
		return (NULL);
	while (++i < len && tmp)
	{
		coord[i] = tmp->coord;
		tmp = tmp->next;
	}
	return (ft_mapclear(&lst), coord);
}
