#include "fdf.h"

void	ft_mapclear(t_map **lst)
{
	t_map	*tmp;
	t_map	*t;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		t = tmp;
		tmp = tmp->next;
		free(t);
	}
	*lst = NULL;
}
