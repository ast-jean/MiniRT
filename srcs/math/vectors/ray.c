/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/21 13:38:32 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"



t_Ray ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray ray;
	ray.origin = o;
	ray.direction = d;
}

t_Ray ray_init_to_screen(t_Vars *vars, int x, int y)
{
	t_Vector3d c_coords = Point3d_to_Vector3d(vars->camera->coord);
	t_Vector3d c_dir = Point3d_to_Vector3d(vars->camera->orientation);
	double dy = 1.0;
	double dx = 1.0;
	double py = (- HEIGHT / 2.0) + dy * ((double)y + 0.5);
	double px = (- WIDTH / 2.0) + dx * ((double)x + 0.5);
	
	//should be calculated once
    t_Vector3d planeCenter = Vector3d_add(c_coords, Vector3d_mult(c_dir, vars->camera->FOV));  
	t_Vector3d planeDirectionX = Vector3d_unit(Vector3d_cross(c_dir, Vector3d_init(0.0, -1.0, 0.0)));
	t_Vector3d planeDirectionY = Vector3d_cross(Vector3d_mult(c_dir, -1.0), c_coords);


	t_Vector3d p = Vector3d_add(planeCenter, Vector3d_add(Vector3d_mult((planeDirectionX, px), Vector3d_mult((planeDirectionY, py)));	
	t_Vector3d unit_dir = Vector3d_unit(Vector3d_sub(p, c->position));
	return ray_init(c_coords, unit_dir);
}

int32_t ray_trace(const t_Ray *ray, t_Vars vars)
{
	
}