bool intersectRayPlane(t_vector3d ray_origin, t_vector3d ray_direction, t_vector3d plane_point, t_vector3d plane_normal, double *t)
{
	double	denom;

	denom = vector3d_dot(plane_normal, ray_direction);
	if (fabs(denom) < 1e-6)
		return (false);
	*t = vector3d_dot(vector3d_sub \
	(plane_point, ray_origin), plane_normal) / denom;
	return (*t >= 0);
}
