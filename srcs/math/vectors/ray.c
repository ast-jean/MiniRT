/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/04/04 11:49:54 by ast-jean         ###   ########.fr       */
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

t_Ray *ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray *ray = malloc(sizeof(t_Ray));
	ray->o = o;
	ray->d = d;
	return ray;
}

t_Ray *ray_init_to_screen(t_Vars *v, int x, int y)
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
	t_Ray *ray =  ray_init(c_coords, ray_dir);
	return (ray);
}

t_Ray *bounce_light(t_Vars *vars, t_Ray_hit *hit)
{
	t_Ray *light_ray;

	light_ray = ray_init(*hit->coord, Point3d_to_Vector3d(vars->light->coord));

	// draw_ray(light_ray, hit->coord->x, hit->coord->y, 250);

	light_ray->d = Point3d_to_Vector3d(vars->light->coord);
	light_ray->o = *hit->coord;
	return (light_ray);
}

bool light_is_visible(t_Vars *vars, t_Ray_hit *hit)
{
	t_Ray *light_ray;
	t_node *node;
	double distance;

	distance = 10000;

	light_ray = bounce_light(vars, hit);
	node = vars->objs->first;

	ray_checkhit(light_ray, hit, &distance);

	if (distance == 10000)
		return (true);
	else
		return (false);
}

// void draw_ray(t_Ray *ray, double x, double y, double distance)
// {
//     int i;
//     int x2, y2;
//     int color = 0xFFFFFF; // couleur du rayon (blanc)
// 	t_Vars *vars = init_vars();

//     // On calcule les coordonnées du deuxième point du rayon
//     x2 = x + (ray->direction.x * distance);
//     y2 = y + (ray->direction.y * distance);

//     // On dessine une ligne entre les deux points
//     mlx_put_pixel(vars->img, x, y, color);
//     mlx_put_pixel(vars->img, x2, y2, color);
//     for (i = 1; i < distance; i++)
//     {
//         mlx_put_pixel(vars->img,  x + (ray->direction.x * i), y + (ray->direction.y * i), color);
//     }
// }
