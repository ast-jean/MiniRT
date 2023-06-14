/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:25:43 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 16:33:47 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector3d	point3d_to_vector3d(t_3dPoint point)
{
	t_vector3d	vec;

	vec.x = to_double(point.x);
	vec.y = to_double(point.y);
	vec.z = to_double(point.z);
	return (vec);
}

t_3dPoint	vec3d_to_point3d(t_vector3d vec)
{
	t_3dPoint	point;

	point.x = fp_init(vec.x);
	point.y = fp_init(vec.y);
	point.z = fp_init(vec.z);
	return (point);
}

t_fixed	fp_init(double value)
{
	t_fixed	fp;

	set_value(&fp, value);
	return (fp);
}

void	set_value(t_fixed *fp, double value)
{
	fp->value = value * FP_SCALE;
}

double	to_double(t_fixed fp)
{
	return ((double) fp.value / FP_SCALE);
}
