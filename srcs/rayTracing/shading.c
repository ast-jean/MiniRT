#include "../../include/miniRT.h"
#include <math.h>

/// @brief Find the shape normal from the shape origin and a coordinates
/// @param hit 
/// @param shape 
/// @return 
t_Vector3d	find_normal(t_Vector3d coords, t_shape shape)
{
		if (ft_strcmp(shape.id, "sp"))
			return (Vector3d_norm(Vector3d_sub(coords, Point3d_to_Vector3d(shape.coord))));
		if (ft_strcmp(shape.id, "pl"))
			return (Point3d_to_Vector3d(shape.orientation));
		// if (ft_strcmp(hit.shape->id, "cy"))
			// return (/*cylinder normal*/);
	return(Vector3d_init(0,0,0));
}

double	find_angle_normals(t_Vector3d Norm1, t_Vector3d Norm2)
{
	double mag1;
	double mag2;
	double dot;

	dot = Vector3d_dot(Norm1, Norm2);
	mag1 = sqrt((Norm1.x * Norm1.x) + (Norm1.y * Norm1.y) + (Norm1.z * Norm1.z));
	mag2 = sqrt((Norm2.x * Norm2.x) + (Norm2.y * Norm2.y) + (Norm2.z * Norm2.z));
	return (dot / (fabs(mag1) * fabs(mag2)));
}

/// @brief 
/// @param ray = the ray from the hit coord to the light
/// @param hit_light = Info of the object hit from the bounce.
/// @param first_hit = Info of the first object hit.
/// @param shape = the source shape
/// @return 
t_rgba shading_obj(t_Ray ray, t_Ray_hit *hit_light, t_shape shape, t_Ray_hit *first_hit, t_rgba color_shape)
{
	t_rgba	color_to_add;
	t_rgba	color = rgba_init(0,0,0);
	t_Vector3d light_dir;
	t_Vector3d obj_normal;
	double coeff;

	light_dir = find_normal(Point3d_to_Vector3d(init_vars()->light->coord), shape);
	obj_normal = find_normal(first_hit->coord, shape);
	coeff = find_angle_normals(light_dir, obj_normal); //asign var

	if (hit_light->hit == false) //in light
	{
		color_to_add = mix_colors_light(*hit_light, ray, coeff, color_shape);
		color = rgba_add(color, color_to_add);
		// color = rgba_add(color, ambient());
	}
	else	//in shadow
		// color = rgba_add(color, ambient());
	
	return (color);
}

/// @brief 		:Returns the color of the pixel depending on object
/// @param hit 	:Information on the intersected point
/// @return 	:Color in rgba form
t_rgba	shading(t_Ray_hit *hit, t_rgba color)
{
	t_rgba		rgba = rgba_init(0,0,0);
	t_Vector3d	lc;
	t_Ray		ray_s2l;	// Ray from shape to the light
	double		distance;	// Distance from hit point to light
	t_Ray_hit	bounce;
	
	lc = Point3d_to_Vector3d(init_vars()->light->coord);
	ray_s2l = ray_init(hit->coord, Vector3d_norm(Vector3d_sub(hit->coord, lc))); //from shape to light
	distance = find_distance(hit->coord, lc); 

	bounce = ray_trace(ray_s2l, distance, hit->shape);
	// ray_s2l.o = lc; //useful?
	rgba = shading_obj(ray_s2l, &bounce, *hit->shape, hit, color);
	return (rgba);
}

