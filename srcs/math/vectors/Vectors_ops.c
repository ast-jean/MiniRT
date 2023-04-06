/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/06 17:43:33 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"


t_Vector3d  Vector3d_add(t_Vector3d a, t_Vector3d b){
    return (Vector3d_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_Vector3d  Vector3d_sub(t_Vector3d a, t_Vector3d b){
    return (Vector3d_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_Vector3d  Vector3d_mult(t_Vector3d v, float b){
    return (Vector3d_init(v.x * b, v.y * b, v.z * b));
}

t_Vector3d  Vector3d_div(t_Vector3d v, float b){
    return (Vector3d_mult(v, 1.0f / b));
}

t_Vector3d  Vector3d_unit(t_Vector3d v){
    double is = sqrtf(powf(v.x,2.0f) + powf(v.y,2.0f) + powf(v.z,2.0f));
    if (!is)
        is = 1;
    return (Vector3d_mult(v, is));
}

