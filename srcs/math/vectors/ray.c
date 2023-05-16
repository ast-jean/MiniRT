/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:53:50 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/15 23:27:32 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Ray	ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray	ray;

	ray.o = o;
	ray.d = d;
	return (ray);
}

//gives the normalized ray direction from Vec_from to Vec_to
t_Vector3d	ray_direction(t_Vector3d from, t_Vector3d to)
{
	t_Vector3d	dir;

	dir = vector3d_sub(to, from);
	return (vector3d_norm(dir));
}

t_Vector3d	screen(t_Vector3d c_coords, t_Vector3d c_dir, double px, double py)
{
	t_Vector3d	up;
	t_Vector3d	right;
	t_Vector3d	screen_position;

	up = vector3d_unit(vector3d_cross \
	(vector3d_cross(c_dir, vector3d_init(0, 1, 0)), c_dir));
	right = vector3d_unit(vector3d_cross(c_dir, up));
	screen_position = vector3d_add(c_coords, vector3d_add \
	(vector3d_mult(c_dir, init_vars()->distance_to_screen), \
	vector3d_add(vector3d_mult(right, px), vector3d_mult(up, py))));
	return (screen_position);
}

t_Ray	ray_init_to_screen(t_Vars *v, int x, int y)
{
	t_Vector3d	c_coords;
	t_Vector3d	c_dir;
	double		px;
	double		py;
	t_Vector3d	ray_dir;

	c_coords = point3d_to_vector3d(v->camera->coord);
	c_dir = point3d_to_vector3d(v->camera->orientation);
	px = ((2.0 * (double)x / \
	(double)WIDTH) - 1.0) * ((double)WIDTH / (double)HEIGHT);
	py = 1 - (2.0 * (double)y / (double)HEIGHT);
	ray_dir = vector3d_unit(vector3d_sub \
	(screen(c_coords, c_dir, px, py), c_coords));
	return (ray_init(c_coords, ray_dir));
}
