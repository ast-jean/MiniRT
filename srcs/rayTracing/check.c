/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/19 20:02:44 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/// @brief Checks if the dot product of 
///			both normal vectors created from the sphere is the same sign
/// @param shape_pos position vector of the shape.
/// @param Vec1 position vector of the vec1.
/// @param Vec2 position vector of the vec2.
/// @return true if same sign and false if not
bool	check_dot_sign(t_Vector3d shape_pos, t_Vector3d Vec1, t_Vector3d Vec2)
{
	double	dot1;
	double	dot2;

	dot2 = vector3d_dot(shape_pos, Vec2);
	dot1 = vector3d_dot(shape_pos, Vec1);
	if (dot1 >= 0 && dot2 >= 0)
		return (true);
	else if (dot1 >= 0 && dot2 >= 0)
		return (true);
	else
		return (false);
}

bool	check_sp(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double *dist)
{
	t_Vector3d	ro_sc;
	t_Vector3d	abc;
	t_Vector2d	t;
	double		distance;
	
	ro_sc = vector3d_sub(ray.o, point3d_to_vector3d(s->coord));
	abc.x = vector3d_dot(ray.d, ray.d);
	abc.y = 2.0 * vector3d_dot(ray.d, ro_sc);
	abc.z = vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2.0);
	if (!solve_quadratic(abc, &t))
		return (false);
	if (t.x > 0)
		distance = t.x;
	else if (t.y > 0)
		distance = t.y;
	else
		return (false);
	if (distance < *dist)
	{
		*dist = distance;
		rh->coord = vector3d_add(ray.o, vector3d_mult(ray.d, distance));
		rh->color = s->color;
		rh->shape = (t_shape *) s;
		rh->distance = find_distance(ray.o, rh->coord);
		rh->hit = true;
		return (true);
	}
	return (false);
}

bool	check_pl(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double *dist)
{
	t_Vector3d	sc;
	t_Vector3d	so;
	double		denom;
	double		t;

	so = vector3d_norm(point3d_to_vector3d(s->orientation));
	sc = point3d_to_vector3d(s->coord);
	denom = vector3d_dot(so, ray.d);
	if (fabs(denom) > 0)
	{
		t = vector3d_dot(vector3d_sub(sc, ray.o), so) / denom;
		if (t < *dist)
		{
			if (t > 0)
			{
				*dist = t;
				rh->color = s->color;
				rh->shape = (t_shape *) s;
				rh->coord = vector3d_add(ray.o, vector3d_mult(ray.d, t));
				rh->distance = t;
				rh->hit = true;
				return (true);
			}
		}
	}
	return (false);
}



// Calcule les vecteurs d et e
void calculate_vectors(const t_Ray r, const t_shape *c, t_Vector3d *d, t_Vector3d *e) {
    t_Vector3d dp = vector3d_sub(r.o, point3d_to_vector3d(c->coord));
    t_Vector3d normalized_orientation = vector3d_norm(point3d_to_vector3d(c->orientation));
    *d = vector3d_sub(r.d, vector3d_mult(normalized_orientation, vector3d_dot(r.d, normalized_orientation)));
    *e = vector3d_sub(dp, vector3d_mult(normalized_orientation, vector3d_dot(dp, normalized_orientation)));
}

// Calcule le discriminant
double calculate_discriminant(const t_Vector3d abc) {
    return abc.y * abc.y - 4 * abc.x * abc.z;
}

// Échange t0 et t1 si t0 > t1
void swap_t_values(double *t0, double *t1) {
    if (*t0 > *t1) {
        double temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
}

// Calcule les points d'intersection P0 et P1
void calculate_intersection_points(const t_Ray r, double t0, double t1, t_Vector3d *P0, t_Vector3d *P1) {
    *P0 = vector3d_add(r.o, vector3d_mult(r.d, t0));
    *P1 = vector3d_add(r.o, vector3d_mult(r.d, t1));
}

// Calcule les hauteurs h0 et h1
void calculate_heights(const t_shape *c, t_Vector3d P0, t_Vector3d P1, double *h0, double *h1) {
    t_Vector3d normalized_orientation = vector3d_norm(point3d_to_vector3d(c->orientation));
    t_Vector3d c1 = vector3d_sub(point3d_to_vector3d(c->coord), vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
    t_Vector3d c2 = vector3d_add(point3d_to_vector3d(c->coord), vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
    *h0 = vector3d_dot(vector3d_sub(P0, c1), vector3d_sub(c2, c1));
    *h1 = vector3d_dot(vector3d_sub(P1, c1), vector3d_sub(c2, c1));
}

// Vérifie si une intersection est valide et met à jour rh et dist
bool check_and_update_intersection(t_shape *c, const t_Ray r, t_Ray_hit *rh, double *dist, double t, bool hit) {
    if (hit) {
        *dist = t;
        rh->distance = *dist;
        rh->color = c->color;
        rh->shape = (t_shape *)c;
        rh->hit = true;
        rh->coord = vector3d_add(r.o, vector3d_mult(r.d, *dist));
        return true;
    }
    return false;
}

bool check_cy(const t_shape *c, const t_Ray r, t_Ray_hit *rh, double *dist)
{
    t_Vector3d d, e;
    calculate_vectors(r, c, &d, &e);
	
    t_Vector3d abc = {vector3d_dot(d, d), 2 * vector3d_dot(d, e), vector3d_dot(e, e) - to_double(c->radius) * to_double(c->radius)};
    double discr = calculate_discriminant(abc);
    if (discr < 0) return false; // no intersection

    double sqrt_discr = sqrt(discr);
    double t0 = (-abc.y - sqrt_discr) / (2 * abc.x);
    double t1 = (-abc.y + sqrt_discr) / (2 * abc.x);
    swap_t_values(&t0, &t1);

    t_Vector3d P0, P1;
    calculate_intersection_points(r, t0, t1, &P0, &P1);

    double h0, h1;
    calculate_heights(c, P0, P1, &h0, &h1);

    if (h0 < 0 || h0 > to_double(c->height) * to_double(c->height)) {
        return check_and_update_intersection((t_shape *)c, r, rh, dist, t1, (h1 >= 0 && h1 <= to_double(c->height) * to_double(c->height) && *dist >= t1));
    } else {
        return check_and_update_intersection((t_shape *)c, r, rh, dist, t0, (h1 >= 0 && *dist >= t0));
    }
}


/// @brief 			:Check for the intersection
///						 of each object with the provided t_Ray
/// @param ray		:The ray
/// @param rh		:The t_Ray_hit containing intersection information
/// @param distance :The distance to compare 
///						if dist == old_dist nothing is intersected
/// @param shape_o	:The object(self) it needs to ignore
/// @return			:Returns a bool if the ray hit(True) or not(false) an object
void	ray_checkhit(t_Ray ray, t_Ray_hit *rh, double *d, t_shape *o)
{
	t_node	*aff;
	t_shape	*s;

	aff = init_vars()->objs->first;
	while (aff)
	{
		s = aff->content;
		if (!o || s->index != o->index)
		{
			if (ft_strcmp(s->id, "pl"))
				check_pl(s, ray, rh, d);
			else if (ft_strcmp(s->id, "sp"))
				check_sp(s, ray, rh, d);
			else if (ft_strcmp(s->id, "cy"))
				check_cy(s, ray, rh, d);
		}
		aff = aff->next;
	}
}
