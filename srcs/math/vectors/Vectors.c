/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:34:27 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/24 12:02:31 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

void  print_Vector(char *title, t_Vector3d a)
{
    printf("%s.x=%f, %s.y=%f, %s.z=%f\n",title, a.x,title, a.y,title, a.z);
}


t_Vector3d Vector3d_init(double x, double y, double z){
    t_Vector3d v;
    v.x = x, v.y = y, v.z = z;
    return v;
}

double  Vector3d_dot(t_Vector3d a, t_Vector3d b){
    double res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return (res);
}

t_Vector3d  Vector3d_cross(t_Vector3d a, t_Vector3d b){
    t_Vector3d v;
    v.x = (a.y * b.z) - (b.y * a.z);
    v.y = (a.z * b.x) - (b.z * a.x);
    v.z = (a.x * b.y) - (b.x * a.y);
    return v;
}

//Calculate the magnitude of the vector
double  Vector3d_length(t_Vector3d v){
    return sqrt(pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
}

//Return the normalized vector
t_Vector3d Vector3d_norm(const t_Vector3d v)
{
    t_Vector3d result;
    double length = Vector3d_length(v);
    if (length == 0)
        return Vector3d_init(0,0,0);
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    return result;
}