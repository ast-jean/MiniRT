#include "../../include/miniRT.h"

/// @brief 
/// @param ray = the ray from the hit coord to the light
/// @param hit_light = Info of the object hit from the bounce.
/// @param first_hit = Info of the first object hit.
/// @param shape = the source shape
/// @return 
t_rgba	shading_obj(t_Ray_hit hit_light, t_shape shape, t_Ray_hit *first_hit, t_Vector3d l_c)
{
	t_rgba		color;
	t_Vector3d	light_dir;
	t_Vector3d	obj_normal;
	double		coeff;

	color = rgba_init(0,0,0);
	light_dir = light_normal(first_hit->coord, l_c);
	obj_normal = find_normal(first_hit->coord, Point3d_to_Vector3d(shape.coord), shape);
	coeff = fmax(0,find_angle_normals(light_dir, obj_normal));
	color = rgba_add(color, mix_colors_light(hit_light, shape, coeff));
	return (color);
}

/// @brief 		:Returns the color of the pixel depending on object and light position
/// @param hit 	:Information on the intersected point
/// @return 	:Color in rgba form
t_rgba	shading(t_Ray_hit *hit)
{
	t_Vector3d	lc;
	t_Ray		ray_s2l;
	double		distance;
	t_Ray_hit	bounce;

	lc = Point3d_to_Vector3d(init_vars()->light->coord);
	ray_s2l = ray_init(hit->coord, Vector3d_norm(Vector3d_sub(hit->coord, lc))); //from shape to light
	distance = find_distance(hit->coord, lc);
	ray_s2l.o = lc;
	bounce = ray_trace(ray_s2l, distance, hit->shape); //can be put in rgba
	return (shading_obj(bounce, *hit->shape, hit, lc));
}
