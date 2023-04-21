#include "../../include/miniRT.h"

double	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double dist)
{
	t_Vector3d ro_sc = Vector3d_sub(ray.o, Point3d_to_Vector3d(s->coord));
	t_Vector3d abc;
	t_Vector2d t;


	abc.x =  Vector3d_dot(ray.d, ray.d);
	abc.y = 2.0 * Vector3d_dot(ray.d, ro_sc);
	abc.z = Vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2.0);

	// printf("A = %f, B = %f, C = %f\n", abc.x, abc.y, abc.z);
	// printf("A = %f, B = %f, C = %f\n", abc.x, abc.y, abc.z);
	double disc;
	double distance;
	if (!solveQuadratic(abc, &t, &disc))
		return (dist);
		distance = t.x;
	if (dist >= distance) //distance comparaison
	{
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		return (distance);
	}
	return (dist);
}

double	check_pl(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double dist)
{
	t_Vector3d sc = Point3d_to_Vector3d(s->coord);
	t_Vector3d so = Point3d_to_Vector3d(s->orientation);

	double denom = Vector3d_dot(so, ray.d);
	if (fabs(denom) > 0){
		double t = Vector3d_dot(Vector3d_sub(sc, ray.o), so) / denom;	
		if(dist >= t) //distance comparaison
		{
			if (t > 0) //only if t is positive
			{
				rh->color = s->color;
				rh->shape = (t_shape*)s;
				rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, t));
				return t;
			}
			else
				return (dist);
		}
	}
	return (dist);
}

double	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh, double dist)
// {
// 	(void)rh;
// 	(void)dist;

// 	t_Vector3d pos = {
// 		ray.o.x - to_double(s->coord.x),
// 		ray.o.y - to_double(s->coord.y),
// 		ray.o.z - to_double(s->coord.z),
//     };

// 	t_Vector3d abc = {
// 		pow(ray.d.x, 2) + pow(ray.d.y, 2),
// 		2 * (ray.d.x * pos.x + ray.d.y * pos.y),
// 		pow(pos.x, 2) + pow(pos.y, 2) - pow(to_double(s->radius), 2)
// 	};

// 	double discriminant = pow(abc.y, 2) - 4 * abc.x * abc.z;

//     if (discriminant < 0.0)
// 	{
//         return false;
//     }

// 	double t0 = (-abc.y - sqrtf(discriminant)) / (2 * abc.x);
//     double t1 = (-abc.y + sqrtf(discriminant)) / (2 * abc.x);

// 	double t = t0 < t1 ? t0 : t1;

// 	double z = ray.o.z + t * ray.d.z;

// 	if (z >= to_double(s->coord.z) && z <= to_double(s->coord.z )+ to_double(s->height)) {
//         *out_t = t;
//         return true;
//     }

//     return false;
// }






{
	// Calculer l'équation du rayon
	t_Vector3d abc;
	t_Vector2d t;

	// Calculer les coefficients de l'équation quadratique
	abc.x = (ray.d.x * ray.d.x) + (ray.d.y * ray.d.y);
	abc.y = 2.0 * (ray.o.x * ray.d.x + ray.o.y * ray.d.y);
	abc.z = (ray.o.x * ray.o.x) + (ray.o.y * ray.o.y) - to_double(s->radius) * to_double(s->radius);

	// printf("A = %f, B = %f, C = %f\n", abc.x, abc.y, abc.z);
	// calculer le discriminant
	double discriminant;

	// Vérifier si le rayon intersecte le cylindre
	if (!solveQuadratic(abc, &t, &discriminant))
		return dist;

	// Choisir la plus petite distance positive
	double distance = 0;
	if (t.x > 0.0 && (t.y < 0.0 || t.x < t.y)) 
	{
		// Vérifier si l'intersection est dans la hauteur du cylindre
		double z1 = ray.o.z + t.x * ray.d.z;
		
		if (z1 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z1 <= to_double(s->coord.z) + to_double(s->height )/ 2.0) 
			distance = t.x;
	}
	if (distance < 0.0) 
	{
		if (t.y > 0.0 && (t.x < 0.0 || t.y < t.x)) 
		{
			// Vérifier si l'intersection est dans la hauteur du cylindre
			double z2 = ray.o.z + t.y * ray.d.z;
			
			if (z2 >= to_double(s->coord.z) - to_double(s->height) / 2.0 && z2 <= to_double(s->coord.z) + to_double(s->height )/ 2.0)
				distance = t.y;
		}
	}
	// Vérifier si une intersection a été trouvée
	if (distance)
		return dist;
	// Remplir la structure t_Ray_hit avec les informations de l'intersection
	if(dist > distance)
	{
		rh->distance = distance;
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
		return distance;
	}
	return dist;
}

bool	ray_checkhit(const t_Ray ray, t_Ray_hit *rh, double *distance, t_shape *shape_o)
{
	t_node *aff = init_vars()->objs->first;
	double dist = *distance;

	while(aff)
	{
		t_shape *s = aff->content;
		// if (!shape_o || s->index != shape_o->index) //if the object is not itself
		// {
			(void)shape_o;
			if (ft_strcmp(s->id, "cy"))
				*distance = check_cy(s, ray, rh, *distance);
			else if (ft_strcmp(s->id, "pl"))
				*distance = check_pl(s, ray, rh, *distance);
			else if (ft_strcmp(s->id, "sp"))
				*distance = check_sp(s, ray, rh, *distance);
		// }
		aff = aff->next;
	}
	if (*distance == dist) 
		return (false); //if the distance is the same it has touch nothing
	else
		return (true);
}
