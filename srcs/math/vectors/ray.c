/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:53:50 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/12 16:14:08 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_ray	ray_init(t_vector3d o, t_vector3d d)
{
	t_ray	ray;

	ray.o = o;
	ray.d = d;
	return (ray);
}

t_vector3d	ray_direction(t_vector3d from, t_vector3d to)
{
	t_vector3d	dir;

	dir = vector3d_sub(to, from);
	return (vector3d_norm(dir));
}

t_vector3d	screen(t_vector3d c_coords, t_vector3d c_dir, double px, double py)
{
	t_vector3d	up;
	t_vector3d	right;
	t_vector3d	screen_position;

	up = vector3d_unit(vector3d_cross \
	(vector3d_cross(c_dir, vector3d_init(0, 1, 0)), c_dir));
	right = vector3d_unit(vector3d_cross(c_dir, up));
	screen_position = vector3d_add(c_coords, vector3d_add(vector3d_mult(c_dir, \
	init_vars()->distance_to_screen * 0.05), \
	vector3d_add(vector3d_mult(right, px), vector3d_mult(up, py))));
	return (screen_position);
}

t_ray	ray_init_to_screen(t_vars *v, int x, int y)
{
	t_vector3d	c_coords;
	t_vector3d	c_dir;
	double		px;
	double		py;
	t_vector3d	ray_dir;

	c_coords = point3d_to_vector3d(v->camera->coord);
	c_dir = point3d_to_vector3d(v->camera->orientation);
	px = ((2.0 * x / \
	WIDTH) - 1.0) * (WIDTH / HEIGHT);
	py = 1 - (2.0 * y / HEIGHT);
	ray_dir = vector3d_unit(vector3d_sub \
	(screen(c_coords, c_dir, px, py), c_coords));
	return (ray_init(c_coords, ray_dir));
}
