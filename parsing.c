#include "fdf.h"
#include <string.h>
#include <errno.h>

t_map *parsing(int fd)
{
	char *line = 0;

	t_map *head = NULL;
	t_map *initial = NULL;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		int len = 0;
		char **points = ft_split(line, ' ');
		while (points[len])
			len++;
		int **coords = ft_calloc(len + 1, sizeof(int *));
		coords[len] = NULL;
		int i = 0;
		while (i < len)
		{
			char **info = ft_split(points[i], ',');
			int *coord = ft_calloc(2, sizeof(int));
			coord[0] = ft_atoi(info[0]);
			coord[1] = 0xffffff;
			if (info[1])
				coord[1] = hextodec(info[1]);
			coords[i] = coord;
			i++;
		}
		int j = 0;
		printf("{");
		while (j < len)
		{
			printf("[%d, %d], ", coords[j][0], coords[j][1]);
			j++;
		}
		printf("}\n");
		if (!initial && head)
		{
			initial = head;
		}
		if (initial && initial->len != (size_t)len)
		{
			return (NULL);
		}
		map_push_back(&head, coords, len);
	}
	return (head);
}
int ft_mapsize(t_map *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
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
		printf("\n%d\n", ft_mapsize(cords));
	}
}