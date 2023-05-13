#include "../../include/miniRT.h"
#include <math.h>

t_Vector3d	light_normal(t_Vector3d coords, t_Vector3d obj_coord)
{
	return (Vector3d_mult(Vector3d_norm(Vector3d_sub(coords, obj_coord)),-1));
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

t_Vector3d	plane_normal(t_Vector3d hit_coords, t_Vector3d orientation)
{
	t_Vector3d light_dir;
	light_dir = light_normal(hit_coords, Point3d_to_Vector3d(init_vars()->light->coord));
	if (Vector3d_dot(orientation, light_dir) < 0)
		return (Vector3d_mult(orientation, -1));
	else
		return (orientation);
}

t_Vector3d	find_normal(t_Vector3d coords, t_Vector3d obj_coord, t_shape shape)
{
	if (ft_strcmp(shape.id, "sp"))
		return (Vector3d_norm(Vector3d_sub(coords, obj_coord)));
	else if (ft_strcmp(shape.id, "pl"))
		return (plane_normal(coords, Point3d_to_Vector3d(shape.orientation)));
	else if (ft_strcmp(shape.id, "cy"))
		return (cylinder_normal(coords, Point3d_to_Vector3d(shape.coord), Point3d_to_Vector3d(shape.orientation)));
	else
		return(Vector3d_init(0,0,0));
}

double	find_angle_normals(t_Vector3d Norm1, t_Vector3d Norm2)
{
	double mag1;
	double mag2;
	double dot;

	dot = Vector3d_dot(Norm1, Norm2);
	mag1 = sqrt((Norm1.x * Norm1.x) + (Norm1.y * Norm1.y) + (Norm1.z * Norm1.z));
	mag2 = sqrt((Norm2.x * Norm2.x) + (Norm2.y * Norm2.y) + (Norm2.z * Norm2.z));
	return (dot / (fabs(mag1) * fabs(mag2)));
}
