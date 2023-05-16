/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:34:27 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/15 22:35:53 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Vector3d	vector3d_init(double x, double y, double z)
{
	t_Vector3d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	vector3d_dot(t_Vector3d a, t_Vector3d b)
{
	double	res;

	res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (res);
}

t_Vector3d	vector3d_cross(t_Vector3d a, t_Vector3d b)
{
	t_Vector3d	v;

	v.x = (a.y * b.z) - (b.y * a.z);
	v.y = (a.z * b.x) - (b.z * a.x);
	v.z = (a.x * b.y) - (b.x * a.y);
	return (v);
}

//Calculate the magnitude of the vector
double	vector3d_length(t_Vector3d v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

//Return the normalized vector
t_Vector3d	vector3d_norm(const t_Vector3d v)
{
	t_Vector3d	result;
	double		length;

	length = vector3d_length(v);
	if (length == 0)
		return (vector3d_init(0, 0, 0));
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}
