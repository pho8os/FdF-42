/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:41:50 by absaid            #+#    #+#             */
/*   Updated: 2022/12/14 01:30:54 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>
#include <errno.h>
int filelen(int fd)
{
	char *line;
	int len;

	len = 0;
	line = get_next_line(fd);
	if(!line)
		return (0);
	len++;
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	free(line);
	close(fd);
	return(len);
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

int ***parsing(int fd, int size, int *len)
{
	t_pars	ptr;
	
	ptr.i = 0;
	*len = 0;
	ptr.coords = ft_calloc(size + 1, sizeof(int **));
	ptr.line = get_next_line(fd);
	if (!ptr.line)
		return (NULL);
	while (ptr.line)
	{
		ptr.len = 0;
		ptr.coords[ptr.i] = line_to_cords(ptr.line, &ptr.len);
		if(!ptr.i && !*len)
			*len = ptr.len;
		if(*len && ptr.len != *len)
			return(NULL);
		free(ptr.line);
		ptr.line = get_next_line(fd);
		ptr.i++;
	}
	return (free(ptr.line), ptr.coords);
}
