#include "fdf.h"
#include <string.h>
#include <errno.h>

void struct_init(t_pars **structo)
{
	(*structo)->head = NULL;
	(*structo)->initial = NULL;
}

int *chartoint(char *str)
{
	char **info;
	int *ret;

	info = ft_split(str,',');
	ret = ft_calloc(2,sizeof(int));
	ret[0] = ft_atoi(info[0]);
	ret[1] = 0xffffff;
	if (info[1])
	{
		ret[1] = hextodec(info[1]);
		if(ret[1] == 0)
			ret[1] = 0xffffff;
	}
	while(*info)
		free(*info++);
	free(str);
	return(ret);
}
int **line_to_cords(char *line , int *len)
{
	char **points;
	int **coords;
	int i;

	i = -1;
	points = ft_split(line, 32);
	while (points[*len])
			(*len)++;
	coords = ft_calloc(*len + 1, sizeof(int *));
	while (++i < *len)
		coords[i] = chartoint(points[i]);
	free(points);
	return(coords);
}
t_map *parsing(int fd)
{
	t_pars *ptr;

	struct_init(&ptr);
	ptr->line = get_next_line(fd);
	if(!ptr->line)
		return (NULL);
	while (ptr->line)
	{
		ptr->len = 0;
		ptr->coords = line_to_cords(ptr->line,&ptr->len);
		if (!ptr->initial && ptr->head)
			ptr->initial = ptr->head;
		if (ptr->initial && ptr->initial->len != (size_t)ptr->len)
			return (NULL);
		map_push_back(&ptr->head, ptr->coords, ptr->len);
		free(ptr->line);
		ptr->line = get_next_line(fd);
	}
	free(ptr->line);
	return (ptr->head);
}
int	ft_mapsize(t_map *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
int ***get_coords(t_map *lst)
{
	int		***coord;
	t_map	*tmp;
	int		i;
	int		len;

	tmp = lst;
	len = ft_mapsize(tmp);
	i = -1;
	tmp = lst;
	coord = ft_calloc(len + 1,sizeof(int *));
	if (!coord)
		return (NULL);
	while (++i < len  && tmp)
	{
		coord[i] = tmp->coord;
		tmp = tmp->next;
	}
	ft_mapclear(&lst);
	return (coord);
}
// int main(int ac ,char **av)
// {
// 	if (ac > 1)
// 	{
// 		char *filename = av[1];
// 		int fd = open(filename, O_RDONLY);
// 		if (fd < 0)
// 			return (fprintf(stderr, "%s\n", strerror(errno)), 1);
// 		t_map *cords = parsing(fd);
// 		int ***coord = get_coords(cords);
// 		// while(1);

// 	}
// }
	
