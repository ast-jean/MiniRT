#include "../../include/miniRT.h"

bool	check_sp(const t_shape *s,const t_Ray *ray, t_Ray_hit *rh)
{
	// t_Vector3d L = Vector3d_sub(ray->o, Point3d_to_Vector3d(s->coord));
    // double t_ca = Vector3d_dot(L, ray->d);
    // // if (t_ca < 0) // The ray is pointing away from the sphere
    // //     return (printf("away from sphere\n"),false);
    // double d2 = Vector3d_dot(L, L) - t_ca * t_ca;
    // double radius_squared = (to_double(s->radius)) * (to_double(s->radius));
    // if (d2 > radius_squared) // The ray misses the sphere
    //     return (printf("ray misses\n"),false);
    // double t_hc = sqrt(radius_squared - d2);
    // double t0 = t_ca - t_hc;
    // double t1 = t_ca + t_hc;

    // // Choose the smaller positive t value
    // double t = (t0 < t1 && t0 > 0) ? t0 : t1;

    // // Calculate the hit coordinates
    // rh->coord->x = ray->o.x + t * ray->d.x;
    // rh->coord->y = ray->o.y + t * ray->d.y;
    // rh->coord->z = ray->o.z + t * ray->d.z;

    // return (true);

    t_Vector3d ro_sc = Vector3d_sub(ray->o, Point3d_to_Vector3d(s->coord));
	double a =  Vector3d_dot(ray->d, ray->d);
    double b = 2.0 * Vector3d_dot(ray->d, ro_sc);
    double c = Vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2);
    double disc = pow(b, 2) - 4 * a * c;
    if (disc < 0)
        return (false);
    double distSqrt = sqrt(disc);
	double q;
	if (b < 0.0)
		q = (-b - distSqrt) / 2.0;
	else
		q = (-b + distSqrt) / 2.0;
    double t0 = q / a;
    double t1 = c / q;
    if (t0 > t1) {
        double tmp = t0;
        t0 = t1;
        t1 = tmp;
    }
    if (t1 < 0)
        return false;
	else if(t0 < 0)
        rh->distance = t1;
	else
        rh->distance = t0;
    *rh->coord = Vector3d_mult(ray->d,rh->distance);
	return true;
}

bool	check_pl(const t_shape *s,const t_Ray *ray, t_Ray_hit *rh)
{
	t_Vector3d sc = Point3d_to_Vector3d(s->coord);
	t_Vector3d so = Point3d_to_Vector3d(s->orientation);

	double denom = Vector3d_dot(so, ray->d);
	if (fabs(denom) > 1e-6){
		double t = Vector3d_dot(Vector3d_sub(sc, ray->o), so) / denom;	
		rh->distance = t;
		*rh->coord = Vector3d_mult(ray->d, t);
		return (t >= 0);
	}
	return (false);
}

bool	check_cy(const t_shape *s,const  t_Ray *ray, t_Ray_hit *rh)
{
	(void)s, (void)ray, (void)rh;
	return (0);

}

void ray_checkhit(const t_Ray *ray, t_Ray_hit *rh, double *distance){
	t_Vars *vars = init_vars();
	t_node *aff = vars->objs->first;
	rh->color = 0;
	rh->distance = INFINITY; 
	rh->shape = NULL;
	while(aff)
	{
		t_shape *s = aff->content;
		if (ft_strcmp(s->id, "sp"))
		{
			if (check_sp(s, ray, rh))
			{	
				rh->distance = find_distance(ray->o, *rh->coord);
				if(rh->distance < *distance)
				{
					rh->shape = s;
					*distance = rh->distance;
					rh->color = s->color;
					// continue;
				}
			}
		}
		else if (ft_strcmp(s->id, "pl"))
		{
			if (check_pl(s, ray, rh))
			{
				rh->distance = find_distance(ray->o, *rh->coord);
				if(rh->distance < *distance)
				{
					rh->shape = s;
					*distance = rh->distance;
					rh->color = s->color;
			// continue;
				}
			}
		}
		// else if (ft_strcmp(s->id, "cy")){
		// 	rh = check_cy(s, ray, rh);
		// 	rh.shape = *s;
		//	continue;
		// }
		aff = aff->next;
	}
}
