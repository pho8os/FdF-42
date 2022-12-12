#include"fdf.h"

t_point	iso(t_point p)
{
	t_point p1;

	p1 = p;
    p1.x = (p.x - p.y) * cos(0.523599);
    p1.y = -p.z + (p.x + p.y) * sin(0.523599);
	return(p1);
}
