/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/03 16:18:50 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//Changes the degree into gradient
double	deg2grad(double deg)
{
	return (deg * (M_PI / 180.0));
}

// "clamps" value into the min and max
uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

//find distance between 2 coords
double	find_distance(t_Vector3d A, t_Vector3d B)
{
    double dx = B.x - A.x;
    double dy = B.y - A.y;
    double dz = B.z - A.z;

    return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}