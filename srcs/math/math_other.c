/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/04 15:36:38 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	deg2grad(double deg)
{
	return (deg * (M_PI / 180.0));
}

uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	find_distance(t_vector3d A, t_vector3d B)
{
	double	dx;
	double	dy;
	double	dz;

	dx = B.x - A.x;
	dy = B.y - A.y;
	dz = B.z - A.z;
	return (sqrt((dx * dx) + (dy * dy) + (dz * dz)));
}
