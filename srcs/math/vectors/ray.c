/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/11 17:10:41 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

t_Ray ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray ray;
	ray.o = o;
	ray.d = d;
	return ray;
}

t_Ray ray_init_to_screen(t_Vars *v, int x, int y)
{
	t_Vector3d c_coords = Point3d_to_Vector3d(v->camera->coord);
	t_Vector3d c_dir = Point3d_to_Vector3d(v->camera->orientation);
	t_Vector3d *screen_position = malloc(sizeof(t_Vector3d));
	t_Vector3d reference_up = Vector3d_init(0,1,0);
	
	double py;
	double px;
	
	px = ((2 * (double)x / (double)WIDTH) - 1) * ((double)WIDTH / (double)HEIGHT);
	py = 1 - (2 * (double)y / (double)HEIGHT);

	t_Vector3d up = Vector3d_unit(Vector3d_cross(Vector3d_cross(c_dir, reference_up), c_dir));
	t_Vector3d right = Vector3d_unit(Vector3d_cross(c_dir, up));

	*screen_position = Vector3d_add(c_coords,Vector3d_add(Vector3d_mult(c_dir, init_vars()->distance_to_screen), Vector3d_add(Vector3d_mult(right, px), Vector3d_mult(up, py))));
	t_Vector3d ray_dir = Vector3d_unit(Vector3d_sub(*screen_position, c_coords));
	t_Ray ray =  ray_init(c_coords, ray_dir);
	return (ray);
}

t_Ray bounce_light(t_Vars *vars, t_Ray_hit *hit)
{
	t_Ray light_ray;
	t_Vector3d light_coor = Point3d_to_Vector3d(vars->light->coord);
	light_ray = ray_init(hit->coord, Vector3d_norm(Vector3d_sub(hit->coord, light_coor)));
	return (light_ray);
}

bool	light_is_visible(t_Vars *vars, t_Ray_hit *hit)
{
	t_Ray		light_ray = bounce_light(vars, hit);
	t_Vector3d	lc = Point3d_to_Vector3d(vars->light->coord);
	double		distance = find_distance(hit->coord, lc);
	t_Ray_hit	bounce = ray_trace(light_ray, distance);

	// if (ft_strcmp(hit->shape->id, "sp")) //sphere shading
	// 	hit->color = shading_sp(hit->color, light_ray, *hit);

	if (hit->color == (uint32_t)0xFFC0CBFF) //debug
	{
		printf("rh.x=%f |rh.y=%f |rh.z=%f\n", hit->coord.x,hit->coord.y,hit->coord.z); 
		printf("Dist Bef= %f\n", distance); //debug
		if (bounce.shape)
			printf("Shape= %s\n", bounce.shape->id); //debug
		else
			printf("Shape= Null\n"); //debug
	}
	if (!bounce.shape && !bounce.color)//if the shape is NULL so has touched nothing
		return (true);
	else
		return (false);
}
