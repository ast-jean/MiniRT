#include "../../include/miniRT.h"

/// @brief Checks if the dot product of both normal vectors created from the sphere is the same sign
/// @param shape_pos position vector of the shape.
/// @param Vec1 position vector of the vec1.
/// @param Vec2 position vector of the vec2.
/// @return true if same sign and false if not
bool	check_dot_sign(t_Vector3d shape_pos, t_Vector3d Vec1, t_Vector3d Vec2) //TODO: This shit broken
{
	double dot1 = Vector3d_dot(shape_pos, Vec1);
	double dot2 = Vector3d_dot(shape_pos, Vec2);

	if (dot1 >= 0 && dot2 >= 0)
		return (true);
	else if (dot1 >= 0 && dot2 >= 0)
		return (true);
	else
		return (false);
}

/// @brief :Checking in which side the object is from the ray used for lighting since the object
/// 		the other side of the camera are not visible.
/// @param ray.o is the light coords and ray.d is the light direction to the hit coords.
/// @param shape the object to locate side
/// @return return true if the object is the same side and false if on the other side
bool	check_side(t_Ray ray, t_shape shape)
{
	t_Vector3d s_coord = Point3d_to_Vector3d(shape.coord);
	ray.d = Vector3d_mult(ray.d, -1);
	// ray.o
	return (check_dot_sign(s_coord, ray.d, ray_direction(ray.o, s_coord)));
}

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
	// if (dist >= distance && check_side(ray, *s)) //distance comparaison
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
	if (fabs(denom) > 0)
	{
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

    t_matrice3x3 inverse_matrix = inverse_matrice3x3(transformation_matrix);

    transformed_ray.o = Point3d_to_Vector3d(rotation_point(inverse_matrix, Vec3D_to_point3D(ray.o)));
    transformed_ray.d = Point3d_to_Vector3d(rotation_point(inverse_matrix, Vec3D_to_point3D(ray.d)));

    return transformed_ray;
}



bool intersectRayPlane(t_Vector3d ray_origin, t_Vector3d ray_direction, t_Vector3d plane_point, t_Vector3d plane_normal, double *t)
{
	double denom = Vector3d_dot(plane_normal, ray_direction);
	if (fabs(denom) < 1e-6)
		return false; // Le rayon est parallèle au plan

	*t = Vector3d_dot(Vector3d_sub(plane_point, ray_origin), plane_normal) / denom;

	return (*t >= 0);
}
t_Vector3d cylinder_normal(t_Vector3d intersection, t_Vector3d C, t_Vector3d V)
{
    // Calculer le vecteur temporaire
    t_Vector3d temp_vec = Vector3d_sub(intersection, C);

    // Projeter temp_vec sur le plan perpendiculaire à l'axe du cylindre (V)
    double scalar_proj = Vector3d_dot(temp_vec, V);
    t_Vector3d proj_V = Vector3d_mult(V, scalar_proj);
    t_Vector3d proj_vec = Vector3d_sub(temp_vec, proj_V);

    // Normaliser le vecteur proj_vec pour obtenir la normale
    t_Vector3d normal_vec = Vector3d_norm(proj_vec);

    return normal_vec;
}

t_rgba calculate_lighting(t_Ray_hit *rh, const t_Vector3d *normal)
{
	t_rgba final_color = {0, 0, 0, 0};
	t_rgba ambient_color = {30, 30, 30, 30}; // À changer pour la vrai lumière ambiante
	t_rgba current_color = separate_color_rgba(rh->color);

	t_Vector3d L = Vector3d_sub(Point3d_to_Vector3d(init_vars()->light->coord), rh->coord);
	double distance = Vector3d_length(L);
	L = Vector3d_norm(L);
	double dot_product = Vector3d_dot(*normal, L);

	if (dot_product > 0)
	{
		double intensity = (to_double(init_vars()->light->light_ratio) * dot_product / (distance * distance));
		final_color.r += (int)(intensity * current_color.r);
		final_color.g += (int)(intensity * current_color.g);
		final_color.b += (int)(intensity * current_color.b);
	}

	// Ajouter l'éclairage ambiant
	final_color.r = clamp(final_color.r + ambient_color.r, 0, 255);
	final_color.g = clamp(final_color.g + ambient_color.g, 0, 255);
	final_color.b = clamp(final_color.b + ambient_color.b, 0, 255);

	return final_color;
}


double check_cy(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double *dist)
{
    t_Vector3d C = Point3d_to_Vector3d(s->coord);
    t_Vector3d V = Point3d_to_Vector3d(s->orientation);
    double r = to_double(s->radius);
    double maxm = to_double(s->height);

    t_Vector3d X = Vector3d_sub(ray.o, C);
    t_Vector3d abc;

    abc.x = ray.d.x * ray.d.x - pow(ray.d.x * V.x, 2) + ray.d.y * ray.d.y - pow(ray.d.y * V.y, 2) + ray.d.z * ray.d.z - pow(ray.d.z * V.z, 2);
    abc.y = 2 * (X.x * ray.d.x - X.x * V.x * ray.d.x * V.x + X.y * ray.d.y - X.y * V.y * ray.d.y * V.y + X.z * ray.d.z - X.z * V.z * ray.d.z * V.z);
    abc.z = X.x * X.x - pow(X.x * V.x, 2) + X.y * X.y - pow(X.y * V.y, 2) + X.z * X.z - pow(X.z * V.z, 2) - r * r;

    double discriminant;
    t_Vector2d t;
    if (!solveQuadratic(abc, &t, &discriminant))
        return *dist;

    double min_distance = INFINITY;
    int i = 0;
    while (i < 2)
    {
        double curr_t = (i == 0) ? t.x : t.y;
        if (curr_t > 0)
        {
            double m = ray.d.x * V.x * curr_t + X.x * V.x + ray.d.y * V.y * curr_t + X.y * V.y + ray.d.z * V.z * curr_t + X.z * V.z;
            if (m >= 0 && m <= maxm)
            {
                if (curr_t < min_distance)
                {
                    min_distance = curr_t;
                    rh->distance = min_distance;
                    rh->color = s->color;
                    rh->shape = (t_shape *)s;
                    rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, min_distance));
                    *dist = min_distance;
                    return (*dist);
                }
            }
        }
        i++;
    }
    return *dist;
}


// double	check_cy(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double *dist)
// {
// 	// Paramètres du cylindre
// 	t_Vector3d C = Point3d_to_Vector3d(s->coord); // point de départ de l'axe du cylindre
// 	t_Vector3d V = Point3d_to_Vector3d(s->orientation); // orientation du cylindre (vecteur unitaire)
// 	double r = to_double(s->radius); // rayon du cylindre
// 	double maxm = to_double(s->height); // longueur de l'axe du cylindre

// 	// Variables intermédiaires
// 	t_Vector3d X = Vector3d_sub(ray.o, C);
// 	// t_Vector3d DV = Vector3d_mult(ray.d, V);
// 	// t_Vector3d XV = Vector3d_mult(X, V);
//     t_Vector3d abc;

// 	// Coefficients de l'équation quadratique
// 	abc.x = ray.d.x * ray.d.x - pow(ray.d.x * V.x, 2) + ray.d.y * ray.d.y - pow(ray.d.y * V.y, 2) + ray.d.z * ray.d.z - pow(ray.d.z * V.z, 2);
// 	abc.y = 2 * (X.x * ray.d.x - X.x * V.x * ray.d.x * V.x + X.y * ray.d.y - X.y * V.y * ray.d.y * V.y + X.z * ray.d.z - X.z * V.z * ray.d.z * V.z);
// 	abc.z = X.x * X.x - pow(X.x * V.x, 2) + X.y * X.y - pow(X.y * V.y, 2) + X.z * X.z - pow(X.z * V.z, 2) - r * r;

// 	// Résoudre l'équation quadratique
// 	double discriminant;
// 	t_Vector2d t;
// 	if (!solveQuadratic(abc, &t, &discriminant))
// 		return *dist;

// 	// Vérifier les intersections avec le cylindre et ses extrémités
// 	double min_distance = INFINITY;
// 	for (int i = 0; i < 2; ++i) {
// 		double curr_t = (i == 0) ? t.x : t.y;
// 		if (curr_t > 0) {
// 			double m = ray.d.x * V.x * curr_t + X.x * V.x + ray.d.y * V.y * curr_t + X.y * V.y + ray.d.z * V.z * curr_t + X.z * V.z;
// 			if (m >= 0 && m <= maxm) {
// 				if (curr_t < min_distance) {
// 					min_distance = curr_t;
// 					rh->distance = min_distance;
// 					rh->color = s->color;
// 					rh->shape = (t_shape*)s;
// 					rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, min_distance));
// 					*dist = min_distance;
// 					return (*dist);
// 				}
// 			}
// 		}
// 	}
// 	return *dist;
// }

// double check_cy(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double *dist)
// {
//     // Paramètres du cylindre
//     t_Vector3d C = Point3d_to_Vector3d(s->coord);      // point de départ de l'axe du cylindre
//     t_Vector3d V = Point3d_to_Vector3d(s->orientation); // orientation du cylindre (vecteur unitaire)
//     double r = to_double(s->radius);                 // rayon du cylindre
//     double maxm = to_double(s->height);              // longueur de l'axe du cylindre

//     t_Vector3d X = Vector3d_sub(ray.o, C);
//     t_Vector3d abc;

//     // Coefficients de l'équation quadratique
//     abc.x = ray.d.x * ray.d.x - pow(ray.d.x * V.x, 2) + ray.d.y * ray.d.y - pow(ray.d.y * V.y, 2) + ray.d.z * ray.d.z - pow(ray.d.z * V.z, 2);
//     abc.y = 2 * (X.x * ray.d.x - X.x * V.x * ray.d.x * V.x + X.y * ray.d.y - X.y * V.y * ray.d.y * V.y + X.z * ray.d.z - X.z * V.z * ray.d.z * V.z);
//     abc.z = X.x * X.x - pow(X.x * V.x, 2) + X.y * X.y - pow(X.y * V.y, 2) + X.z * X.z - pow(X.z * V.z, 2) - r * r;

//     double discriminant;
//     t_Vector2d t;
//     if (!solveQuadratic(abc, &t, &discriminant))
//         return *dist;

//     // Vérifier les intersections avec le cylindre et ses extrémités
//     double min_distance = INFINITY;
//     for (int i = 0; i < 2; ++i)
//     {
//         double curr_t = (i == 0) ? t.x : t.y;
//         if (curr_t > 0)
//         {
//             double m = ray.d.x * V.x * curr_t + X.x * V.x + ray.d.y * V.y * curr_t + X.y * V.y + ray.d.z * V.z * curr_t + X.z * V.z;
//             if (m >= 0 && m <= maxm)
//             {
//                 if (curr_t < min_distance)
//                 {
//                     min_distance = curr_t;
//                     rh->distance = min_distance;
//                     rh->color = s->color;
//                     rh->shape = (t_shape *)s;
//                     rh->coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, min_distance));
//                     *dist = min_distance;
//                 }
//             }
//         }
//     }

//     // Vérifier les intersections avec les extrémités du cylindre
//     t_Vector3d base_point = C;
//     t_Vector3d top_point = Vector3d_add(C, Vector3d_mult(V, maxm));
//     double t_plane;

//     for (int i = 0; i < 2; ++i)
//     {
//         t_Vector3d plane_point = (i == 0) ? base_point : top_point;
//         if (intersectRayPlane(ray.o, ray.d, plane_point, V, &t_plane))
//         {
//             t_Vector3d intersection_point = Vector3d_add(ray.o, Vector3d_mult(ray.d, t_plane));
//             t_Vector3d vec_from_center = Vector3d_sub(intersection_point, plane_point);

//             if (Vector3d_length(vec_from_center) <= r)
//             {
//                 if (t_plane < min_distance)
//                 {
//                     min_distance = t_plane;
//                     rh->distance = min_distance;
//                     rh->color = s->color;
//                     rh->shape = (t_shape *)s;
//                     rh->coord = intersection_point;
//                     *dist = min_distance;
//                 }
//             }
//         }
//     }

//     return *dist;
// }

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
                *distance = check_cy(s, ray, rh, distance);
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
