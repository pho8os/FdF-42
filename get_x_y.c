#include"fdf.h"

// destination.x = source.x + cos(angle) * source.z - cos(angle) * source.y
// destination.y = -source.y * sin(angle) - source.z * sin(angle)


t_point  get_x_y(t_point *p1)
{
	t_point s1;
	t_point s2;
	t_point s3;

	s1.x = p1->x + (cos(90) * p1->z) - (cos(90) * p1->y);
	s1.y = -1 * (p1->y * sin(90)) - (p1->z * sin(90));
	return(s1);
}