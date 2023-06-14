/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/12 16:14:09 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector3d	vector3d_add(t_vector3d a, t_vector3d b)
{
	return (vector3d_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector3d	vector3d_sub(t_vector3d a, t_vector3d b)
{
	return (vector3d_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vector3d	vector3d_mult(t_vector3d v, double b)
{
	return (vector3d_init(v.x * b, v.y * b, v.z * b));
}

t_vector3d	vector3d_mult3d(t_vector3d v, t_vector3d b)
{
	return (vector3d_init(v.x * b.x, v.y * b.y, v.z * b.z));
}

t_vector3d	vector3d_unit(t_vector3d v)
{
	double	length;

	length = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	if (length == 0)
		return (v);
	return (vector3d_mult(v, 1.0 / length));
}
