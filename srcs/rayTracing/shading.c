#include "../../include/miniRT.h"
#include <math.h>

/// @brief 
/// @param ray = the ray from the hit coord to the light
/// @param hit_light = Info of the object hit from the bounce.
/// @param first_hit = Info of the first object hit.
/// @param shape = the source shape
/// @return 
t_rgba shading_obj(t_Ray ray, t_Ray_hit hit_light, t_shape shape, t_Ray_hit *first_hit, t_Vector3d l_c)
{
	t_rgba	color_to_add;
	t_rgba	color = rgba_init(0,0,0);
	t_Vector3d light_dir;
	t_Vector3d obj_normal;
	double coeff;


	light_dir = light_normal(first_hit->coord, l_c);
	obj_normal = find_normal(first_hit->coord, Point3d_to_Vector3d(shape.coord), shape);
	coeff = find_angle_normals(light_dir, obj_normal);

	color_to_add = mix_colors_light(hit_light, ray, shape, coeff);
	color = rgba_add(color, color_to_add);

	return (color);
}

/// @brief 		:Returns the color of the pixel depending on object and light position
/// @param hit 	:Information on the intersected point
/// @return 	:Color in rgba form
t_rgba	shading(t_Ray_hit *hit)
{

	t_rgba		rgba;
	t_Vector3d	lc;
	t_Ray		ray_s2l;	// Ray from shape to the light
	
	lc = Point3d_to_Vector3d(init_vars()->light->coord);
	ray_s2l = ray_init(hit->coord, Vector3d_norm(Vector3d_sub(hit->coord, lc))); //from shape to light
	double distance = find_distance(hit->coord, lc); //can be put in bounce
	
	ray_s2l.o = lc;
	ray_s2l.d = Vector3d_mult(ray_s2l.d, -1);

	t_Ray_hit bounce = ray_trace(ray_s2l, distance, hit->shape); //can be put in rgba
	rgba = shading_obj(ray_s2l, bounce, *hit->shape, hit, lc);
	return (rgba);
}
