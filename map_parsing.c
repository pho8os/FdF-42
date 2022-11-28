#include"fdf.h"
int double_len(char **s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return(i);
}

int **parsing(char *line)
{
	char **splt_32;
	char **infos;
	int **cord;
	int i;

	i = -1;
	splt_32 = ft_split(line,' ');
	if(!splt_32)
		return (NULL);
	cord = ft_calloc(double_len(splt_32),sizeof(int *));
	while(++i < double_len(splt_32))
	{
		infos = ft_split(splt_32[i], ',');
		if(infos)
			return(NULL);
		cord[i] = ft_calloc(2,sizeof(int));
		if(!cord[i])
			return(NULL);
		cord[i][0] = ft_atoi(infos[0]); 
		cord[i][1] = 0xffffff;
		if(cord[i][1])
			cord[i][1] = hextodec(infos[1]);
	}
	return(cord);	
}

int ***get_cords(int fd)
{
	char **lines;
	int i;
	int j;
	int ***cords;

	i = 0;
	j = 0;
	while((lines[i] = get_next_line(fd)))
		i++;
	cords = ft_calloc(i + 1, sizeof(int **));
	while(j < i)
	{
		cords[j] = parsing(lines[j]);
		j++;
	}
	return (cords);
}

int main(int ac, char **av)
{
	int ***tab;
	int i = 0;
	int j = 0;
	if (ac > 1)
	{
		char *filename = av[1];
		int fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (fprintf(stderr, "%s\n", strerror(errno)), 1);
		tab = get_cords(fd);
		while(i < 4)
		{
			while(j < 4)
			{
				printf("[%d , %d]",tab[i][j][0],tab[i][j][0]);
				j++;
			}
			printf("\n");
			i++;
		}
		
	}
}