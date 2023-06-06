/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:55:10 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/06 19:06:27 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector3d	light_normal(t_vector3d coords, t_vector3d obj_coord)
{
	return (vector3d_mult(vector3d_norm(vector3d_sub(coords, obj_coord)), -1));
}

t_vector3d	cylinder_normal(t_vector3d intersection, \
t_vector3d C, t_vector3d V, t_vector3d L, t_ray ray)
{
	t_vector3d	intersection_to_center;
	t_vector3d	proj_axis_vec;
	t_vector3d	perpendicular_vec;
	double		scalar_proj;
	// bool		is_light_inside;

	(void)L;
	(void)ray;
	intersection_to_center = vector3d_sub(intersection, C);
	scalar_proj = vector3d_dot(intersection_to_center, V);
	proj_axis_vec = vector3d_mult(V, scalar_proj);
	perpendicular_vec = vector3d_sub(intersection_to_center, proj_axis_vec);
	// is_light_inside = vector3d_dot(L, perpendicular_vec) < 0;
	// if (is_light_inside)
		// perpendicular_vec = vector3d_mult(perpendicular_vec, -1);
	return (vector3d_norm(perpendicular_vec));
}

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

t_vector3d	find_normal(t_vector3d coords, \
t_vector3d obj_coord, t_shape shape, t_ray_hit hit,t_ray ray)
{
	(void)hit;

	if (ft_strcmp(shape.id, "sp"))
		return (vector3d_norm(vector3d_sub(coords, obj_coord)));
	else if (ft_strcmp(shape.id, "pl"))
		return (plane_normal(coords, point3d_to_vector3d(shape.orientation)));
	else if (ft_strcmp(shape.id, "cy"))
			return (cylinder_normal(coords, point3d_to_vector3d(shape.coord),
                        point3d_to_vector3d(shape.orientation), vector3d_norm(vector3d_sub(coords, obj_coord)), ray));

	else
		return (vector3d_init(0, 0, 0));
}

double	find_angle_normals(t_vector3d Norm1, t_vector3d Norm2)
{
	double	mag1;
	double	mag2;
	double	dot;

	dot = vector3d_dot(Norm1, Norm2);
	mag1 = sqrt \
	((Norm1.x * Norm1.x) + (Norm1.y * Norm1.y) + (Norm1.z * Norm1.z));
	mag2 = sqrt \
	((Norm2.x * Norm2.x) + (Norm2.y * Norm2.y) + (Norm2.z * Norm2.z));
	return (dot / (fabs(mag1) * fabs(mag2)));
}
