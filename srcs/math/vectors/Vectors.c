/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:34:27 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/06 17:43:09 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

//Initialize a vector using vars x, y ,z
t_Vector3d Vector3d_init(float x, float y, float z){
    t_Vector3d v;
    v.x = x, v.y = y, v.z = z;
    return v;
}

//Calculate the dot product
float  Vector3d_dot(t_Vector3d a, t_Vector3d b){
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

//Caculate the cross product
t_Vector3d  Vector3d_cross(t_Vector3d a, t_Vector3d b){
    t_Vector3d v;
    v.x = (a.y * b.z) - (b.y * a.z);
    v.y = (a.z * b.x) - (b.z * a.x);
    v.z = (a.x * b.y) - (b.x * a.y);
    return v;
}

//Calculate the magnitude of the vector
float  Vector3d_length(t_Vector3d v)
{
    return sqrtf(powf(v.x,2.0f) + powf(v.y,2.0f) + pow(v.z,2.0f));
}

//Return the normalized vector
t_Vector3d Vector3d_norm(const t_Vector3d v)
{
    t_Vector3d result;
    float length = Vector3d_length(v);
    if (length == 0)
        return (t_Vector3d){0, 0, 0};
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    return result;
}