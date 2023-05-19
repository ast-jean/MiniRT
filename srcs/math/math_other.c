/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/17 11:00:18 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//Changes the degree into gradient
double	deg2grad(double deg)
{
	return (deg * (M_PI / 180.0));
}

// "clamps" value into the min and max in int
uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

//find distance between 2 coords
double	find_distance(t_Vector3d A, t_Vector3d B)
{
	double	dx;
	double	dy;
	double	dz;

	dx = B.x - A.x;
	dy = B.y - A.y;
	dz = B.z - A.z;
	return (sqrt((dx * dx) + (dy * dy) + (dz * dz)));
}

bool	solve_quadratic(t_Vector3d abc, t_Vector2d *t)
{
	double	tmp;
	double	q;
	double discr;

	discr = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (discr < 0)
		return (false);
	else if (discr == 0)
		t->x = t->y = - 0.5 * abc.y / abc.x;
	else
	{
		q = (abc.y > 0) ?
			-0.5 * (abc.y + sqrt(discr)):
			-0.5 * (abc.y - sqrt(discr));
		if (q < 0)
			return (false);
		t->x = q / abc.x;
		t->y = abc.z / q;
	}
	if (t->x > t->y)
	{
		tmp = t->y;
		t->y = t->x;
		t->x = tmp;
	}
	return (true);
}
