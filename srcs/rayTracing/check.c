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
    return true;
}

bool	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh)
{
	(void)s, (void)ray, (void)rh;
	return (0);
}

bool	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh)
{
    // Calculer l'équation du rayon
    t_Vector3d o = ray.origin;
    t_Vector3d d = ray.direction;

    // Calculer les coefficients de l'équation quadratique
    double a = (d.x * d.x) + (d.y * d.y);
    double b = 2.0 * (o.x * d.x + o.y * d.y);
    double c = o.x * o.x + o.y * o.y - s->diameter.value * s->diameter.value / 4.0;

    // calculer le discriminant
    double discriminant = b * b - 4.0 * a * c;

    // Vérifier si le rayon intersecte le cylindre
    if (discriminant < 0.0)
        return false;

    // Calculer les distances entre l'origine du rayon et les points d'intersection possibles
    double t1 = (-b - sqrt(discriminant))  / (2.0 * a);
    double t2 = (-b + sqrt(discriminant))  / (2.0 * a);

    // Choisir la plus petite distance positive
    double distance = -1.0;

    if (t1 > 0.0 && (t2 < 0.0 || t1 < t2)) 
    {
        // Vérifier si l'intersection est dans la hauteur du cylindre
        double z1 = o.z + t1 * d.z;
        
        if (z1 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z1 <= to_double(s->coord.z) + to_double(s->height )/ 2.0) 
            distance = t1;
    }
    
    if (distance < 0.0) 
    {
        if (t2 > 0.0 && (t1 < 0.0 || t2 < t1)) 
        {
            // Vérifier si l'intersection est dans la hauteur du cylindre
            double z2 = o.z + t2 * d.z;
            
            if (z2 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z2 <= to_double(s->coord.z) + to_double(s->height )/ 2.0)
                distance = t2;
        }
    }

    // Vérifier si une intersection a été trouvée
    if (distance < 0.0)
        return false;

    // Remplir la structure t_Ray_hit avec les informations de l'intersection
    rh->distance = distance;
    rh->color = s->color;
    rh->shape = (t_shape*)s;
    rh->coord = (t_Vector3d*)malloc(sizeof(t_Vector3d));
    rh->coord->x = o.x + distance * d.x;
    rh->coord->y = o.y + distance * d.y;
    rh->coord->z = o.z + distance * d.z;

    return true;
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
				if(rh->distance < *distance)
				{
					rh->shape = s;
					*distance = rh->distance;
					rh->color = s->color;
					// *rh->coord = Vector3d_mult(Point3d_to_Vector3d(vars->camera->coord), *distance);
                    *rh->coord = Vector3d_add(ray->origin, Vector3d_mult(ray->direction, rh->distance));
					// continue;
				}
			}
		}
		else if (ft_strcmp(s->id, "cy"))
        {
	        check_cy(s, *ray, rh);
		}
			// printf("in checkhit - color = %X\n", rh.color);
		// else if (ft_strcmp(s->id, "pl")){
		// 	rh = check_pl(s, ray, rh);
		// 	rh.shape = *s;
		//	continue;
		// }
		//	continue;
		aff = aff->next;
	}
}
