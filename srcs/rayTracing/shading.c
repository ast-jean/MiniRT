#include "../../include/miniRT.h"
#include <math.h>


// # The material parameters are constants independant of the object for now
// ambient = 0.4 * Vec3(0.4, 0.4, 1)
// k_ambient = 1
// k_diffuse = 2
// k_specular = 10
// n_specular = 50
// https://github.com/nesvoboda/minirt/blob/master/srcs/shading.c

t_Vector3d	find_normal(t_Ray_hit hit)
{
	if (hit.shape)
	{
	if (ft_strcmp(hit.shape->id, "sp"))
		return (Vector3d_norm(Vector3d_sub(hit.coord, Point3d_to_Vector3d(hit.shape->coord))));
	if (ft_strcmp(hit.shape->id, "pl"))
		return (Point3d_to_Vector3d(hit.shape->orientation));
	// if (ft_strcmp(hit.shape->id, "cy"))
		// return (/*cylinder normal*/);
	}
	return(Vector3d_init(0,0,0));
}

t_rgba shading_obj(t_Ray ray, t_Ray_hit *hit)
{
	t_rgba	color = separate_color_rgba(0); //initialize color
	t_rgba	color_to_add;

	hit->normal = find_normal(*hit);
	// normal_sp(hit->coord, *hit->shape); //only difference between all shading objects
	if (Vector3d_dot(ray.d, hit->normal) > 0)
	{
		// hit->normal  = Vector3d_sub(Vector3d_init(0,0,0),  Vector3d_mult(hit->normal, 1));
		hit->normal =  Vector3d_mult(hit->normal, -1); //same has other
		hit->coeff = fmax(0, Vector3d_dot(hit->coord, ray.d));
	}
	// while(lights) throught all linked listed lights if we add multiple lights bonus
	color_to_add = mix_colors_light(*hit, ray);
	color = rgba_add(color, color_to_add);

	return (color);
}

t_rgba	shading(t_Ray_hit *hit)
{
	t_rgba		rgba = separate_color_rgba(0);
	t_Ray		light_ray = bounce_light(init_vars(), hit);
	t_Vector3d	lc = Point3d_to_Vector3d(init_vars()->light->coord);
	double		distance = find_distance(hit->coord, lc);

	t_Ray_hit	bounce = ray_trace(light_ray, distance, hit->shape);

	//put in shading function in shading.c
		light_ray.o = lc;

	rgba = shading_obj(light_ray, &bounce);

	return (rgba);
}

