/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:34:27 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/21 12:59:53 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Vector3d Vector3d_init(double x, double y, double z){
    t_Vector3d v;
    v.x = x, v.y = y, v.z = z;
    return v;
}

double  Vector3d_dot(t_Vector3d a, t_Vector3d b){
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_Vector3d  Vector3d_cross(t_Vector3d a, t_Vector3d b){
    t_Vector3d v;
    v.x = (a.y * b.z) - (b.y * a.z);
    v.y = (a.z * b.x) - (b.z * a.x);
    v.z = (a.x * b.y) - (b.x * a.y);
    return v;
}

double  Vector3d_length(t_Vector3d v){
    return sqrt(pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
}


