/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:33:32 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/06 18:57:02 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//Changes the degree into gradient
float	deg2grad(float deg)
{
	return (deg * (M_PI / 180.0f));
}

// "clamps" value into the min and max
uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

//find distance between 2 coords
float	find_distance(t_Vector3d A, t_Vector3d B)
{
    float dx = B.x - A.x;
    float dy = B.y - A.y;
    float dz = B.z - A.z;

    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

//Changes the int to a float divided by 100.0f, so 50 is 0.5
float intToFloat(int value)
{
    return value / 100.0f;
}