/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/15 22:49:30 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Vector3d	vector3d_add(t_Vector3d a, t_Vector3d b)
{
	return (vector3d_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_Vector3d	vector3d_sub(t_Vector3d a, t_Vector3d b)
{
	return (vector3d_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_Vector3d	vector3d_mult(t_Vector3d v, double b)
{
	return (vector3d_init(v.x * b, v.y * b, v.z * b));
}

t_Vector3d	vector3d_mult3d(t_Vector3d v, t_Vector3d b)
{
	return (vector3d_init(v.x * b.x, v.y * b.y, v.z * b.z));
}

t_Vector3d	vector3d_unit(t_Vector3d v)
{
	double	length;

	length = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	if (length == 0)
		return (v);
	return (vector3d_mult(v, 1.0 / length));
}
