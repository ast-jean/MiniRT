/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:32:54 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/24 12:14:17 by slavoie          ###   ########.fr       */
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
	t_Vector3d c_dir = Point3d_to_Vector3d(v->camera->orientation);
	t_Vector3d *screen_position = malloc(sizeof(t_Vector3d));
	t_Vector3d reference_up = Vector3d_init(0,1,0);
	
	//Vector 2d
	double py;
	double px;
	
	px = (2 * (double)x / (double)WIDTH) - 1;
	py = 1 - (2 * (double)y / (double)HEIGHT);



	// printf("pcx = %f: pcy = %f: pcz = %f\n", v->planeCenter->x, v->planeCenter->y, v->planeCenter->z);



	// Vector3d_add(*v->planeCenter, \
	// Vector3d_add(Vector3d_mult(*v->planeDirectionX, px), \
	// Vector3d_mult(*v->planeDirectionY, py)));


	t_Vector3d up = Vector3d_unit(Vector3d_cross(Vector3d_cross(c_dir, reference_up), c_dir));
	t_Vector3d right = Vector3d_unit(Vector3d_cross(c_dir, up));

	*screen_position = Vector3d_add(c_coords,Vector3d_add(Vector3d_mult(c_dir, init_vars()->distance_to_screen), Vector3d_add(Vector3d_mult(right, px), Vector3d_mult(up, py))));
	//screen position = camera position + (|viewing direction * distance to screen) + (right vector * x pixel vector) + (up vector * y pixel vector)
	
	//ray direction = normalize(screen position - camera position)
	t_Vector3d ray_dir = Vector3d_unit(Vector3d_sub(*screen_position, c_coords));
	// free(screen_position);


	// ft_putstr_fd("|p.x =",1 );
	// ft_putstr_fd(ft_itoa(screen_position->x), 1);
	// ft_putstr_fd(" p.y =",1 );
	// ft_putstr_fd(ft_itoa(screen_position->y), 1);
	// ft_putstr_fd(" p.z =",1 );
	// ft_putstr_fd(ft_itoa(screen_position->z), 1);
	// ft_putstr_fd("\n",1 );
	// printf("p.x = %f\n: p.y = %f: p.z = %f\n", p.x, p.y, p.z);
	t_Ray *ray =  ray_init(c_coords, ray_dir);
	return (ray);

}
