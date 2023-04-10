/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/10 14:35:48 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Vectors.h"

double round_to_first_digit(double num) {
    double log_val = log10(fabs(num));
    double int_part;
    modf(log_val, &int_part);
    double power = pow(10, int_part);
    return copysign(power, num);
}
double trunc_to_first_digit(double num) {
    double log_val = log10(fabs(num));
    double int_part;
    modf(log_val, &int_part);
    double power = pow(10, int_part- 1);
    return copysign(power, num);
}

t_Ray ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray ray;// = malloc(sizeof(t_Ray));
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
	
	px = ((2 * (double)x / (double)WIDTH) - 1) * ((double)WIDTH/ (double)HEIGHT);
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
	light_ray = ray_init(*hit->coord, Vector3d_norm(Vector3d_sub(*hit->coord, light_coor)));
	return (light_ray);
}

//Return the length of a ray between 2 vectors
float ray_length(t_Vector3d start, t_Vector3d end)
{
	t_Vector3d d = Vector3d_sub(end, start);
    return (sqrt(d.x*d.x + d.y *d.y + d.z * d.z));
}

bool light_is_visible(t_Vars *vars, t_Ray_hit *hit)
{
	t_Ray light_ray;
	double distance = 0;

	t_Vector3d lc = Point3d_to_Vector3d(vars->light->coord);

	distance = ray_length(*hit->coord, lc);
	light_ray = bounce_light(vars, hit);

	/**/if (hit->color == (uint32_t)0xFFC0CBFF) //debug
	{
	/**/	printf("\nLc.x=%f |Lc.y=%f |Lc.z=%f\n", lc.x,lc.y,lc.z); 
	/**/	printf("rh.x=%f |rh.y=%f |th.z=%f\n", hit->coord->x,hit->coord->y,hit->coord->z); 
			printf("Dist Bef= %f\n", distance); //debug

	}

	t_Ray_hit bounce = ray_trace(light_ray, distance);

	/**/if (hit->color == (uint32_t)0xFFC0CBFF) //debug
	/**/	printf("Dist Aft= %f\n", distance); //debug

	if (!bounce.color)//if the shape is NULL so has touched nothing
		return (true);
	else
		return (false);
}
