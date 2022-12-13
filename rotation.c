/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:08:13 by absaid            #+#    #+#             */
/*   Updated: 2022/12/13 02:30:30 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

t_point rot_x(t_point p, double angle)
{
	t_point p2;
	p2 = p;
	p2.x = p.x;
	p2.y = p.y * cos(angle) - (p.z * sin(angle));
	p2.z = (p.y * sin(angle)) + (p.z * cos(angle));
	return(p2);
}

t_point rot_y(t_point p, double angle)
{
	t_point p2;
	
	p2 = p;
	p2.x = p.x * cos(angle) + p.z * sin(angle);
	p2.y = p.y;
	p2.z = p.x * -sin(angle) + p.z * cos(angle);
	return(p2);
}

t_point rot_z(t_point p, double angle)
{
	t_point p2;
	
	p2 = p;
	p2.x = p.x * cos(angle) + p.y * -sin(angle);
	p2.y = p.x * sin(angle) + p.y * cos(angle);
	p2.z = p.z;
	return(p2);
}
