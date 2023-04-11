#include "../../include/miniRT.h"

double	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double *dist)
{
	t_Vector3d ro_sc = Vector3d_sub(ray.o, Point3d_to_Vector3d(s->coord));
	double a =  Vector3d_dot(ray.d, ray.d);
	double b = 2.0 * Vector3d_dot(ray.d, ro_sc);
	double c = Vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2);
	double disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (*dist);
	double distSqrt = sqrt(disc);
	double q;
	if (b < 0.0)
		q = (-b - distSqrt) / 2.0;
	else
		q = (-b + distSqrt) / 2.0;
	double t0 = q / a;
	double t1 = c / q;
	if (t0 > t1) //swap
	{
		double tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	double distance;
	if (t1 < 0)
		return (*dist);
	else if(t0 < 0)
		distance = t1;
	else
		distance = t0;

	if (*dist > distance)
	{
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d,rh->distance));
		return (distance);
	}
	return (*dist);
}

double	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double *dist)
{
	t_Vector3d sc = Point3d_to_Vector3d(s->coord);
	t_Vector3d so = Point3d_to_Vector3d(s->orientation);

	double denom = Vector3d_dot(so, ray.d);
	if (fabs(denom) > 1e-6){
		double t = Vector3d_dot(Vector3d_sub(sc, ray.o), so) / denom;	
		if(*dist > t)
		{
			rh->distance = t;
			rh->color = s->color;
			rh->shape = (t_shape*)s;
			rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, t));
			if (t >=0)
				return t;
			else
				return (*dist);
		}
		return (*dist);
	}
	return (*dist);
}

double	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh, double *dist)
{
	// Calculer l'équation du rayon
	t_Vector3d o = ray.o;
	t_Vector3d d = ray.d;

	// Calculer les coefficients de l'équation quadratique
	double a = (d.x * d.x) + (d.y * d.y);
	double b = 2.0 * (o.x * d.x + o.y * d.y);
	double c = o.x * o.x + o.y * o.y - s->radius.value * s->radius.value;

	// calculer le discriminant
	double discriminant = b * b - 4.0 * a * c;

	// Vérifier si le rayon intersecte le cylindre
	if (discriminant < 0.0)
		return *dist;

	// Calculer les distances entre l'oe du rayon et les points d'intersection possibles
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
		return *dist;

	// Remplir la structure t_Ray_hit avec les informations de l'intersection
	if(*dist > distance)
	{
		rh->distance = distance;
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		rh->coord = Vector3d_add(o, Vector3d_mult(d, distance));
	}
	return distance;
}

void ray_checkhit(const t_Ray ray, t_Ray_hit *rh, double *distance){
	t_Vars *vars = init_vars();
	t_node *aff = vars->objs->first;
	rh->color = 0;
	rh->shape = NULL;
	while(aff)
	{
		t_shape *s = aff->content;
		if (ft_strcmp(s->id, "sp"))
			*distance = check_sp(s, ray, rh, distance);
		else if (ft_strcmp(s->id, "cy"))
			*distance = check_cy(s, ray, rh, distance);
		else if (ft_strcmp(s->id, "pl"))
			*distance = check_pl(s, ray, rh, distance);
		aff = aff->next;
	}
}
