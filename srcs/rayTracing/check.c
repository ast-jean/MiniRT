#include "../../include/miniRT.h"

bool	check_sp(const t_shape *s,const t_Ray *ray, t_Ray_hit *rh)
{
  	double a =  Vector3d_dot(ray->direction, ray->direction);
    t_Vector3d ro_sc = Vector3d_sub(ray->origin, Point3d_to_Vector3d(s->coord));
    double b = 2.0 * Vector3d_dot(ray->direction, ro_sc);
    double c = Vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->diameter)/ 2, 2);
    double disc = pow(b, 2) - 4 * a * c;
    if (disc < 0)
        return (false);
    double distSqrt = sqrt(disc);
    double q = b < 0.0 ? (-b - distSqrt) / 2.0 : (-b + distSqrt) / 2.0;
    double t0 = q / a;
    double t1 = c / q;
    if (t0 > t1) {
        double tmp = t0;
        t0 = t1;
        t1 = tmp;
    }
    if (t1 < 0) {
        return false;
    } else if(t0 < 0) {
        rh->distance = t1;
    } else {
        rh->distance = t0;
    }
    return true;
}

bool	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh)
{
	(void)s, (void)ray, (void)rh;
	return (0);
}

bool	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh)
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
		rh->shape = s;
		if (ft_strcmp(s->id, "sp")){
			if (check_sp(s, ray, rh)){
				if(rh->distance < *distance)
				{
					*distance = rh->distance;
					rh->color = s->color;
				}

			}
			// printf("in checkhit - color = %X\n", rh.color);
		}
		// else if (ft_strcmp(s->id, "pl")){
		// 	rh = check_pl(s, ray, rh);
		// 	rh.shape = *s;
		// }
		// else if (ft_strcmp(s->id, "cy")){
		// 	rh = check_cy(s, ray, rh);
		// 	rh.shape = *s;
		// }
		aff = aff->next;
	}
}
