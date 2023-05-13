/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/13 13:16:40 by ast-jean         ###   ########.fr       */
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
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
// "clamps" value into the min and max in double
double	clampd(double value, double min, double max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

double max(double value1, double value2)
{
	if(value1 > value2)
		return value1;
	else
		return value2;
}

//find distance between 2 coords
double	find_distance(t_Vector3d A, t_Vector3d B)
{
	double dx = B.x - A.x;
	double dy = B.y - A.y;
	double dz = B.z - A.z;

	return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

bool solveQuadratic(t_Vector3d abc, t_Vector2d *t, double *discr)
{
	*discr = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (*discr < 0)
		return false;
	else if (discr == 0) 
		t->x = t->y = - 0.5 * abc.y / abc.x;
	else 
	{
		double q = (abc.y > 0) ?
			-0.5 * (abc.y + sqrt(*discr)):
			-0.5 * (abc.y - sqrt(*discr));
		if (q < 0)
		    return false;
		t->x = q / abc.x;
		t->y = abc.z / q;
	}
	if (t->x > t->y)
	{
		double tmp = t->y;
		t->y = t->x;
		t->x = tmp;
	}
	return true;
}