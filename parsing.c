#include "fdf.h"
#include <string.h>
#include <errno.h>

t_map *parsing(int fd)
{
	char *line;

	t_map *head = NULL;
	t_map *initial = NULL;
	line = get_next_line(fd);
	if(!line)
		return(NULL);
	while (line)
	{
		int len = 0;
		char **info;
		char **points = ft_split(line,32);
		while (points[len])
			len++;
		int **coords = ft_calloc(len + 1, sizeof(int *));
		int i = -1;
		while (++i < len)
		{
			info = ft_split(points[i], ',');
			int *coord = ft_calloc(2, sizeof(int));
			coord[0] = ft_atoi(info[0]);
			coord[1] = 0xffffff;
			if (info[1])
			{
				coord[1] = hextodec(info[1]);
				if(coord[1] == 0)
					coord[1] = 0xffffff;
			}	
			coords[i] = coord;
		}
		if (!initial && head)
			initial = head;
		if (initial && initial->len != (size_t)len)
			return (NULL);
		map_push_back(&head, coords, len);
		free(line);
		line = get_next_line(fd);
	}
	return (head);
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

int main(int ac, char **av)
{
	if (ac > 1)
	{
		char *filename = av[1];
		int fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (fprintf(stderr, "%s\n", strerror(errno)), 1);
		t_map *cords = parsing(fd);
		printf("\n------%d------\n\n", ft_mapsize(cords));
		int ***coord = get_coords(cords);
		int i = -1,j;
		while(coord[++i])
		{
			j = -1;
			while(coord[i][++j])
			{
				printf("[%d,%d]--",coord[i][j][0],coord[i][j][1]);
			}
			printf("\n");
		}
	}
}