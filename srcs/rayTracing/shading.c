#include "../../include/miniRT.h"

int32_t shading_sp(int32_t color, const t_Ray *ray, t_Ray_hit hit){
	t_Vector3d cc = ray->o;
	t_Vector3d cd = ray->d;
	t_Vector3d sc = Point3d_to_Vector3d(hit.shape->coord);
	

	double sr = to_double(hit.shape->radius);
	double t = Vector3d_dot(Vector3d_sub(sc, cc), cd)/ Vector3d_dot(cd, cd) ;
	double c = 0;
	t_Vector3d p = Vector3d_add(cc, Vector3d_mult(cd, t));
	double y = Vector3d_length(Vector3d_sub(sc,p));
	if(y < sr)
	{
		double x = sqrt((sr * sr) - (y * y));
		double t1 = t + x;
		c = remap( sc.y - sr, sc.y, t1);
		color = brightness(color, c);
	}
	return color;
}