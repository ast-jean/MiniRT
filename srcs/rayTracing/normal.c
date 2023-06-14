/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:55:10 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 15:33:53 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector3d	light_normal(t_vector3d coords, t_vector3d obj_coord)
{
	return (vector3d_mult(vector3d_norm(vector3d_sub(coords, obj_coord)), -1));
}

t_vector3d	cylinder_normal(t_vector3d intersection, \
t_vector3d C, t_vector3d V, double radius)
{
	t_vector3d	intersection_to_center;
	t_vector3d	proj_axis_vec;
	t_vector3d	perpendicular_vec;
	double		scalar_proj;
	t_vector3d	light_dir;
	t_vector3d	light_to_center;
	double		distance_to_axis;

	light_dir = vector3d_sub(point3d_to_vector3d \
	(init_vars()->light->coord), intersection);
	intersection_to_center = vector3d_sub(intersection, C);
	scalar_proj = vector3d_dot(intersection_to_center, V);
	proj_axis_vec = vector3d_mult(V, scalar_proj);
	perpendicular_vec = vector3d_sub(intersection_to_center, proj_axis_vec);

	// Calculate the distance from the light source to the cylinder axis
	light_to_center = vector3d_sub(point3d_to_vector3d(init_vars()->light->coord), C);
	distance_to_axis = vector3d_length(vector3d_sub(light_to_center, vector3d_mult(V, vector3d_dot(light_to_center, V))));

	// If the light is inside the cylinder, invert the normal
	if (distance_to_axis < radius)
		perpendicular_vec = vector3d_mult(perpendicular_vec, -1);

	return (vector3d_norm(perpendicular_vec));
}


// t_vector3d	cylinder_normal(t_vector3d intersection, \
// t_vector3d C, t_vector3d V)
// {
// 	t_vector3d	intersection_to_center;
// 	t_vector3d	proj_axis_vec;
// 	t_vector3d	perpendicular_vec;
// 	double		scalar_proj;
// 	t_vector3d	light_dir;


// 	light_dir = vector3d_sub(intersection, point3d_to_vector3d \
// 	(init_vars()->light->coord));
// 	// light_dir = vector3d_sub(point3d_to_vector3d \
// 	// (init_vars()->light->coord), intersection);
// 	intersection_to_center = vector3d_sub(intersection, C);
// 	scalar_proj = vector3d_dot(intersection_to_center, V);
// 	proj_axis_vec = vector3d_mult(V, scalar_proj);
// 	perpendicular_vec = vector3d_sub(intersection_to_center, proj_axis_vec);
// 	// if (vector3d_dot(perpendicular_vec, light_dir) < 0)
// 	// 	perpendicular_vec = vector3d_mult(perpendicular_vec, -1);
// 	// return (vector3d_norm(perpendicular_vec));
// 		// if (vector3d_dot(intersection, perpendicular_vec ) < 0)
// 		// 	return(vector3d_norm(vector3d_mult(perpendicular_vec, -1)));
// 		return (vector3d_norm(perpendicular_vec));
// }

t_vector3d	plane_normal(t_vector3d hit_coords, t_vector3d orientation)
{
	t_vector3d	light_dir;
	t_vars		*vars;

	vars = init_vars();
	light_dir = light_normal \
	(hit_coords, point3d_to_vector3d(vars->light->coord));
	if (vector3d_dot(orientation, light_dir) < 0)
		return (vector3d_mult(orientation, -1));
	else
		return (orientation);
}

t_vector3d	sphere_normal(t_vector3d point_coords, \
t_vector3d sphere_center, t_vector3d light_ray)
{
	t_vector3d	vec;
	t_vector3d	light_coord;
	t_vector3d	normal;

	light_coord = point3d_to_vector3d(init_vars()->light->coord);
	vec = vector3d_sub(point_coords, sphere_center);
	normal = vector3d_norm(vec);
	if (vector3d_dot(normal, light_ray) < 0 && \
	(find_distance(point_coords, sphere_center) > \
	find_distance(sphere_center, light_coord)))
		normal = vector3d_mult(normal, -1);
	return (normal);
}

t_vector3d	find_normal(t_vector3d coords, \
t_vector3d obj_coord, t_shape shape, t_vector3d light_ray)
{
	if (ft_strcmp(shape.id, "sp"))
		return (sphere_normal(coords, obj_coord, light_ray));
	else if (ft_strcmp(shape.id, "pl"))
		return (plane_normal(coords, point3d_to_vector3d(shape.orientation)));
	else if (ft_strcmp(shape.id, "cy"))
		return (cylinder_normal(coords, obj_coord,
				vector3d_norm(point3d_to_vector3d(shape.orientation)), to_double(shape.radius)));
	else
		return (vector3d_init(0, 0, 0));
}
