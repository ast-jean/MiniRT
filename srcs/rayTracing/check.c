#include "../../include/miniRT.h"

bool	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh)
{
    t_Vector3d ro_sc = Vector3d_sub(ray.o, s->coord);
	float a =  Vector3d_dot(ray.d, ray.d);
    float b = 2.0f * Vector3d_dot(ray.d, ro_sc);
    float c = Vector3d_dot(ro_sc, ro_sc) - powf(s->radius, 2.0f);
    float disc = powf(b, 2.0f) - 4.0f * a * c;
    if (disc < 0.0f)
        return (false);
    float distSqrt = sqrtf(disc);
	float q;
	if (b < 0.0f)
		q = (-b - distSqrt) / 2.0f;
	else
		q = (-b + distSqrt) / 2.0f;
    float t0 = q / a;
    float t1 = c / q;
    if (t0 > t1) {
        float tmp = t0;
        t0 = t1;
        t1 = tmp;
    }
    if (t1 < 0.0f)
        return false;
	else if(t0 < 0.0f)
        rh->distance = t1;
	else
        rh->distance = t0;
    *rh->coord = Vector3d_mult(ray.d,rh->distance);
	return true;
}

bool	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh)
{
	t_Vector3d sc = s->coord;
	t_Vector3d so = s->orien;

	float denom = Vector3d_dot(so, ray.d);
	if (fabsf(denom) > 1e-6f){
		float t = Vector3d_dot(Vector3d_sub(sc, ray.o), so) / denom;	
		rh->distance = t;
		*rh->coord = Vector3d_mult(ray.d, t);
		return (t >= 0);
	}
	return (false);
}

bool	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh)
{
    // Calculer l'équation du rayon
    t_Vector3d o = ray.o;
    t_Vector3d d = ray.d;

    // Calculer les coefficients de l'équation quadratique
    float a = (d.x * d.x) + (d.y * d.y);
    float b = 2.0f * (o.x * d.x + o.y * d.y);
    float c = o.x * o.x + o.y * o.y - s->radius * s->radius;

    // calculer le discriminant
    float discriminant = b * b - 4.0f * a * c;

    // Vérifier si le rayon intersecte le cylindre
    if (discriminant < 0)
        return false;

    // Calculer les distances entre l'origine du rayon et les points d'intersection possibles
    float t1 = (-b - sqrtf(discriminant))  / (2.0f * a);
    float t2 = (-b + sqrtf(discriminant))  / (2.0f * a);

    // Choisir la plus petite distance positive
    float distance = -1.0f;

    if (t1 > 0.0f && (t2 < 0.0f || t1 < t2)) 
    {
        // Vérifier si l'intersection est dans la hauteur du cylindre
        float z1 = o.z + t1 * d.z;
        
        if (z1 >= s->coord.z - s->height / 2.0f && z1 <= s->coord.z + s->height / 2.0f) 
            distance = t1;
    }
    
    if (distance < 0.0f) 
    {
        if (t2 > 0.0f && (t1 < 0.0f || t2 < t1)) 
        {
            // Vérifier si l'intersection est dans la hauteur du cylindre
            double z2 = o.z + t2 * d.z;
            
            if (z2 >= s->coord.z - s->height / 2.0f && z2 <= s->coord.z + s->height / 2.0f)
                distance = t2;
        }
    }

    // Vérifier si une intersection a été trouvée
    if (distance < 0.0f)
        return false;

    // // Remplir la structure t_Ray_hit avec les informations de l'intersection
    rh->distance = distance;
    // rh->color = s->color;
    // rh->shape = (t_shape*)s;
    // rh->coord = (t_Vector3d*)malloc(sizeof(t_Vector3d));
    // rh->coord->x = o.x + distance * d.x;
    // rh->coord->y = o.y + distance * d.y;
    // rh->coord->z = o.z + distance * d.z;

    return true;
}

void ray_checkhit(const t_Ray ray, t_Ray_hit *rh, float *distance){
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
				rh->distance = find_distance(ray.o, *rh->coord);
				if(rh->distance < *distance)
				{
					rh->shape = s;
					*distance = rh->distance;
					rh->color = s->color;
                    *rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, rh->distance));
				}
			}
		}
		else if (ft_strcmp(s->id, "cy"))
        {
	        if(check_cy(s, ray, rh))
            {
                rh->distance = find_distance(ray.o, *rh->coord);
                if(rh->distance < *distance)
				{
					rh->shape = s;
					*distance = rh->distance;
					rh->color = s->color;
				}
            }
		}
			// printf("in checkhit - color = %X\n", rh.color);
		// else if (ft_strcmp(s->id, "pl")){
		// 	rh = check_pl(s, ray, rh);
		// 	rh.shape = *s;
		// }
		else if (ft_strcmp(s->id, "pl"))
		{
			if (check_pl(s, ray, rh))
			{
				rh->distance = find_distance(ray.o, *rh->coord);
				if(rh->distance < *distance)
				{
					rh->shape = s;
					*distance = rh->distance;
					rh->color = s->color;
				}
			}
		}
		// else if (ft_strcmp(s->id, "cy")){
		// 	rh = check_cy(s, ray, rh);
		// 	rh.shape = *s;
		//	continue;
		aff = aff->next;
	}
}
