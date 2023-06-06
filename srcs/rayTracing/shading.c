/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:53:59 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/06 18:59:55 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_rgba	shading_obj(t_ray_hit hit_light, t_shape shape, \
t_ray_hit *first_hit, t_vector3d l_c, t_ray ray)
{
	t_rgba		color;	
	t_vector3d	light_dir;
	t_vector3d	obj_normal;
	double		coeff;

	color = rgba_init(0, 0, 0);
	light_dir = light_normal(first_hit->coord, l_c);
	obj_normal = find_normal(first_hit->coord, \
	point3d_to_vector3d(shape.coord), shape, *first_hit, ray);
	coeff = fmax(0, find_angle_normals(light_dir, obj_normal));
	color = rgba_add(color, mix_colors_light(hit_light, shape, coeff));
	return (color);
}


/// @brief 		:Returns the color of the 
///				pixel depending on object and light position
/// @param hit 	:Information on the intersected point
/// @return 	:Color in rgba form
t_rgba	shading(t_ray_hit *hit, t_ray ray)
{
	t_vector3d	lc;
	t_ray		ray_s2l;
	double		distance;
	t_ray_hit	bounce;

	lc = point3d_to_vector3d(init_vars()->light->coord);
	ray_s2l = ray_init(hit->coord, \
	vector3d_norm(vector3d_sub(hit->coord, lc)));
	distance = find_distance(hit->coord, lc);
	ray_s2l.o = lc;
	bounce = ray_trace(ray_s2l, distance, hit->shape);
	return (shading_obj(bounce, *hit->shape, hit, lc, ray));
}
