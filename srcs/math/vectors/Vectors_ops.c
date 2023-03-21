/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/21 17:06:59 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Vector3d  Vector3d_add(t_Vector3d a, t_Vector3d b){
    return (Vector3d_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_Vector3d  Vector3d_sub(t_Vector3d a, t_Vector3d b){
    return (Vector3d_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_Vector3d  Vector3d_mult(t_Vector3d v, double b){
    return (Vector3d_init(v.x * b, v.y * b, v.z * b));
}

t_Vector3d  Vector3d_div(t_Vector3d v, double b){
    return (Vector3d_mult(v, 1.0 / b));
}

t_Vector3d  Vector3d_unit(t_Vector3d v){
    double is = sqrt(pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
    if (!is)
        is = 1;
    return (Vector3d_mult(v, is));
}

