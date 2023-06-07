/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/07 11:42:54 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool	check_sp(const t_shape *s, const t_ray ray, t_ray_hit *rh, double *dist)
{
	t_vector3d	abc;
	t_vector2d	t;
	double		distance;

	abc = assign_var_quad(ray.d, vector3d_sub(ray.o, \
	point3d_to_vector3d(s->coord)), s);
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
// Calcule les vecteurs d et e
void calculate_vectors(const t_ray r, const t_shape *c, t_vector3d *d, t_vector3d *e) {
    t_vector3d dp = vector3d_sub(r.o, point3d_to_vector3d(c->coord));
    t_vector3d normalized_orientation = vector3d_norm(point3d_to_vector3d(c->orientation));
    *d = vector3d_sub(r.d, vector3d_mult(normalized_orientation, vector3d_dot(r.d, normalized_orientation)));
    *e = vector3d_sub(dp, vector3d_mult(normalized_orientation, vector3d_dot(dp, normalized_orientation)));
}

// Calcule le discriminant
double calculate_discriminant(const t_vector3d abc) {
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
void calculate_intersection_points(const t_ray r, double t0, double t1, t_vector3d *P0, t_vector3d *P1) {
    *P0 = vector3d_add(r.o, vector3d_mult(r.d, t0));
    *P1 = vector3d_add(r.o, vector3d_mult(r.d, t1));
}

// Calcule les hauteurs h0 et h1
void calculate_heights(const t_shape *c, t_vector3d P0, t_vector3d P1, double *h0, double *h1) {
    t_vector3d normalized_orientation = vector3d_norm(point3d_to_vector3d(c->orientation));
    t_vector3d c1 = vector3d_sub(point3d_to_vector3d(c->coord), vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
    t_vector3d c2 = vector3d_add(point3d_to_vector3d(c->coord), vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
    *h0 = vector3d_dot(vector3d_sub(P0, c1), vector3d_sub(c2, c1));
    *h1 = vector3d_dot(vector3d_sub(P1, c1), vector3d_sub(c2, c1));
}

// Vérifie si une intersection est valide et met à jour rh et dist
bool check_and_update_intersection(t_shape *c, const t_ray r, t_ray_hit *rh, double *dist, double t, bool hit) {
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



bool check_cy(const t_shape *c, const t_ray r, t_ray_hit *rh, double *dist)
{
    t_vector3d d, e;
    calculate_vectors(r, c, &d, &e);
	
    t_vector3d abc = {vector3d_dot(d, d), 2 * vector3d_dot(d, e), vector3d_dot(e, e) - to_double(c->radius) * to_double(c->radius)};
    double discr = calculate_discriminant(abc);
    if (discr < 0) return false; // no intersection

    double sqrt_discr = sqrt(discr);
    double t0 = (-abc.y - sqrt_discr) / (2 * abc.x);
    double t1 = (-abc.y + sqrt_discr) / (2 * abc.x);
    swap_t_values(&t0, &t1);

    t_vector3d P0, P1;
    calculate_intersection_points(r, t0, t1, &P0, &P1);

    double h0, h1;
    calculate_heights(c, P0, P1, &h0, &h1);

    if (h0 < 0 || h0 > to_double(c->height) * to_double(c->height)) {
        return check_and_update_intersection((t_shape *)c, r, rh, dist, t1, (h1 >= 0 && h1 <= to_double(c->height) * to_double(c->height) && *dist >= t1));
    } else {
        return check_and_update_intersection((t_shape *)c, r, rh, dist, t0, (h0 >= 0 && *dist >= t0));
    }
}

// t_vector2d	find_intersection_dists(t_vector3d abc, double sqrt_discr)
// {
// 	t_vector2d	ts;	

// 	ts.x = (-abc.y - sqrt_discr) / (2 * abc.x);
// 	ts.y = (-abc.y + sqrt_discr) / (2 * abc.x);

// 	return (ts);
// }

// t_vector2d	calculate_t(const t_shape *c, const t_ray r)
// {
// 	t_vector3d	d;
// 	t_vector3d	e;
// 	t_vector3d	abc;
// 	double		discr;

// 	calculate_vectors(r, c, &d, &e);
// 	abc = assign_var_quad(d, e, c);
// 	discr = abc.y * abc.y - 4 * abc.x * abc.z;
// 	return (find_intersection_dists(abc, sqrt(discr)));
// }



// bool	check_cy(const t_shape *c, const t_ray r, t_ray_hit *rh, double *dist)
// {
// 	t_vector2d	t;
// 	t_vector2d	h;
// 	t_vector3d	p0;
// 	t_vector3d	p1;

// 	t = calculate_t(c, r);
// 	if (t.x < 0 || t.y < 0)
// 		return (false);
// 	// swap_quad(&t);
// 	calculate_intersection_points(r, t, &p0, &p1);
// 	calculate_heights(c, p0, p1, &h);
// 	if (h.x < 0 || h.x > to_double(c->height) * to_double(c->height))
// 	{
// 		if (h.y >= 0 && h.y <= to_double(c->height) \
// 		* to_double(c->height) && *dist >= t.y)
// 			return (check_and_update_intersection((t_shape *)c, r, \
// 			rh, (*dist = t.y)));
// 	}
// 	else
// 	{
// 		if (h.x >= 0 && *dist >= t.x)
// 			return (check_and_update_intersection((t_shape *)c, r, \
// 			rh, (*dist = t.y)));
// 	}
// 	return (false);
// }

void	ray_checkhit(t_ray ray, t_ray_hit *rh, double *d, t_shape *o)
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
