#include"fdf.h"

t_point	iso(t_point p, t_data *ptr)
{
	ptr->rz = 0.523599;
	ptr->rx = 0.523599;
	ptr->ry = -0.523599;
	p = rot(p,ptr);
	return (p);
}
