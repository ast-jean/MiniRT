

#include "../../../include/Vectors.h"

t_Ray ray_init(t_Vector3d o, t_Vector3d d)
{
	t_Ray ray;
	ray.o = o;
	ray.d = d;
	return ray;
}

//gives the normalized ray direction from Vec_from to Vec_to
t_Vector3d ray_direction(t_Vector3d from, t_Vector3d to)
{
    t_Vector3d dir = Vector3d_sub(to, from);
    return (Vector3d_norm(dir));
}

t_Ray ray_init_to_screen(t_Vars *v, int x, int y)
{
	t_Vector3d c_coords = Point3d_to_Vector3d(v->camera->coord);
	t_Vector3d c_dir = Point3d_to_Vector3d(v->camera->orientation);
	t_Vector3d reference_up = Vector3d_init(0,1,0);	
	double px = ((2.0 * (double)x / (double)WIDTH) - 1.0) * ((double)WIDTH / (double)HEIGHT);
	double py = 1 - (2.0 * (double)y / (double)HEIGHT);
	t_Vector3d up = Vector3d_unit(Vector3d_cross(Vector3d_cross(c_dir, reference_up), c_dir));
	t_Vector3d right = Vector3d_unit(Vector3d_cross(c_dir, up));
	t_Vector3d screen_position = Vector3d_add(c_coords,Vector3d_add(Vector3d_mult(c_dir, init_vars()->distance_to_screen), Vector3d_add(Vector3d_mult(right, px), Vector3d_mult(up, py))));
	t_Vector3d ray_dir = Vector3d_unit(Vector3d_sub(screen_position, c_coords));
	return (ray_init(c_coords, ray_dir));
}
