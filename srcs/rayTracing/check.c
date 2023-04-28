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
		rh->distance = distance;
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
				rh->distance = t;
				return t;
			}
			else
				return (dist);
		}
	}
	return (dist);
}

t_matrice3x3 inverse_matrice3x3(t_matrice3x3 m)
{
    t_matrice3x3 inv;
    double det;

    inv.m[0][0] = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
    inv.m[0][1] = m.m[0][2] * m.m[2][1] - m.m[0][1] * m.m[2][2];
    inv.m[0][2] = m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1];
    inv.m[1][0] = m.m[1][2] * m.m[2][0] - m.m[1][0] * m.m[2][2];
    inv.m[1][1] = m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0];
    inv.m[1][2] = m.m[0][2] * m.m[1][0] - m.m[0][0] * m.m[1][2];
    inv.m[2][0] = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];
    inv.m[2][1] = m.m[0][1] * m.m[2][0] - m.m[0][0] * m.m[2][1];
    inv.m[2][2] = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];

    det = m.m[0][0] * inv.m[0][0] + m.m[0][1] * inv.m[1][0] + m.m[0][2] * inv.m[2][0];

    if (det == 0)
    {
        fprintf(stderr, "La matrice n'a pas d'inverse (determinant nul)\n");
        exit(EXIT_FAILURE);
    }

    det = 1.0 / det;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            inv.m[i][j] *= det;
        }
    }

    return inv;
}



t_Ray inverse_transform_ray(const t_Ray ray, const t_matrice3x3 transformation_matrix)
{
    t_Ray transformed_ray;

    // Inverse the transformation matrix
    t_matrice3x3 inverse_matrix = inverse_matrice3x3(transformation_matrix);

    // Apply the inverse transformation to the ray origin and direction
    transformed_ray.o = Point3d_to_Vector3d(rotation_point(inverse_matrix, Vec3D_to_point3D(ray.o)));
    transformed_ray.d = Point3d_to_Vector3d(rotation_point(inverse_matrix, Vec3D_to_point3D(ray.d)));

    return transformed_ray;
}


double	check_cy(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double *dist)
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
		return *dist;

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
	if (!distance)
		return *dist;
	// Remplir la structure t_Ray_hit avec les informations de l'intersection
	if(*dist > distance)
	{
		rh->distance = distance;
		rh->color = s->color;
		rh->shape = (t_shape*)s;
		rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
		*dist = distance;
		return distance;
	}
	return *dist;
}


t_matrice3x3 create_matrice(t_shape *s)
{
	t_matrice3x3 rx;
	t_matrice3x3 ry;
	t_matrice3x3 rz;
	t_rotation rotation;

	rotation = vector_to_rotation_angles(Point3d_to_Vector3d(s->orientation));

	rx = matrice_rotation_x(rotation.phi);
	ry = matrice_rotation_y(rotation.theta);
	rz = matrice_rotation_z(rotation.psi);

	return(combine_matrice(rx, ry, rz));
}


bool ray_checkhit(t_Ray ray, t_Ray_hit *rh, double *distance, t_shape *shape_o)
{
    t_node *aff = init_vars()->objs->first;
    double old_dist = *distance;

    while (aff)
    {
        t_shape *s = aff->content;
        if (!shape_o || s->index != shape_o->index) //if the object is not itself
        {
            if (ft_strcmp(s->id, "cy"))
            {
                t_Ray transformed_ray = ray; // Create a copy of the ray for transformation

                t_rotation rotation = vector_to_rotation_angles(Point3d_to_Vector3d(s->orientation));
                t_matrice3x3 inv_m = combine_matrice(matrice_rotation_x(-rotation.phi), matrice_rotation_y(-rotation.theta), matrice_rotation_z(-rotation.psi));

                t_3dPoint tranformed_o = rotation_point(inv_m, Vec3D_to_point3D(ray.o));
                transformed_ray.o = Point3d_to_Vector3d(tranformed_o);
                t_3dPoint tranformed_d = rotation_point(inv_m, Vec3D_to_point3D(ray.d));
                transformed_ray.d = Point3d_to_Vector3d(tranformed_d);

                double new_distance = check_cy(s, transformed_ray, rh, distance);
                if (new_distance < *distance) // Only update if the new distance is smaller
                {
                    *distance = new_distance;

                    t_matrice3x3 m = create_matrice(s);
                    t_3dPoint rotated_intersection = rotation_point(m, Vec3D_to_point3D(rh->coord));
                    rh->coord = Point3d_to_Vector3d(rotated_intersection);
                    rh->normal = Point3d_to_Vector3d(rotation_point(m, Vec3D_to_point3D(rh->normal)));
                }
            }
            else if (ft_strcmp(s->id, "pl"))
                *distance = check_pl(s, ray, rh, *distance);
            else if (ft_strcmp(s->id, "sp"))
                *distance = check_sp(s, ray, rh, *distance);
        }
        aff = aff->next;
    }
    if (*distance == old_dist)
        return (false); //if the distance is the same it has touch nothing
    else
        return (true);
}







// /// @brief 			:Check for the intersection of each object with the provided t_Ray
// /// @param ray		:The ray
// /// @param rh		:The t_Ray_hit containing intersection information
// /// @param distance :The distance to compare if dist == old_dist nothing is intersected
// /// @param shape_o	:The object(self) it needs to ignore
// /// @return			:Returns a bool if the ray hit(True) or not(false) an object
// bool	ray_checkhit(t_Ray ray, t_Ray_hit *rh, double *distance, t_shape *shape_o)
// {
// 	t_node *aff = init_vars()->objs->first;
// 	double old_dist = *distance; //Should dist be distance?

// 	while(aff)
// 	{
// 		t_shape *s = aff->content;
// 		if (!shape_o || s->index != shape_o->index) //if the object is not itself
// 		{
// 			if (ft_strcmp(s->id, "cy"))
// 			{
// 				t_rotation rotation = vector_to_rotation_angles(Point3d_to_Vector3d(s->orientation));
// 				t_matrice3x3 inv_m = combine_matrice(matrice_rotation_x(-rotation.phi), matrice_rotation_y(-rotation.theta), matrice_rotation_z(-rotation.psi));
// 				t_3dPoint tranformed_o = rotation_point(inv_m, Vec3D_to_point3D(ray.o));
// 				ray.o = Point3d_to_Vector3d(tranformed_o);
// 				t_3dPoint tranformed_d = rotation_point(inv_m, Vec3D_to_point3D(ray.d));
// 				ray.d = Point3d_to_Vector3d(tranformed_d);
// 				check_cy(s, ray, rh, distance);

// 				t_matrice3x3 m =  create_matrice(s);
// 				t_3dPoint rotated_intersection =  rotation_point(m, Vec3D_to_point3D(rh->coord));
// 				rh->coord = Point3d_to_Vector3d(rotated_intersection);
// 				rh->normal = Point3d_to_Vector3d(rotation_point(m, Vec3D_to_point3D(rh->normal)));
// 			}
// 			else if (ft_strcmp(s->id, "pl"))
// 				*distance = check_pl(s, ray, rh, *distance);
// 			else if (ft_strcmp(s->id, "sp"))
// 				*distance = check_sp(s, ray, rh, *distance);
// 		}
// 		aff = aff->next;
// 	}
// 	if (*distance == old_dist) 
// 		return (false); //if the distance is the same it has touch nothing
// 	else
// 		return (true);
// }
