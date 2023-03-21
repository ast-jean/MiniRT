/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/21 18:22:02 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Ray *ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray *ray = malloc(sizeof(t_Ray));
	ray->origin = o;
	ray->direction = d;
	return ray;
}

t_Ray *ray_init_to_screen(t_Vars *v, int x, int y)
{
	t_Vector3d c_coords = Point3d_to_Vector3d(v->camera->coord);
	t_Vector3d p;

	//Vector 2d
	double dy = 1.0;
	double dx = 1.0;
	
	//Vector 2d
	double py;
	double px;
	
	py = (- HEIGHT / 2.0) + dy * ((double)y + 0.5);
	px = (- WIDTH / 2.0) + dx * ((double)x + 0.5);
	
	printf("pcx = %f: pcy = %f: pcz = %f\n", v->planeCenter->x, v->planeCenter->y, v->planeCenter->z);

	p = Vector3d_add(*v->planeCenter, \
	Vector3d_add(Vector3d_mult(*v->planeDirectionX, px), \
	Vector3d_mult(*v->planeDirectionY, py)));

	// planecenter + (x*px) + (y*py);

	// printf("p.x = %f\n: p.y = %f: p.z = %f\n", p.x, p.y, p.z);

	t_Vector3d unit_dir = Vector3d_unit(Vector3d_sub(p, c_coords));
	t_Ray *ray =  ray_init(c_coords, unit_dir);
	return (ray);
}
