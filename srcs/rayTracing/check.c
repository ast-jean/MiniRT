/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/17 11:38:31 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	check_sp(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double dist)
{
	t_Vector3d	ro_sc;
	t_Vector3d	abc;
	t_Vector2d	t;
	double		distance;
	double		disc; //Put in solve_quadratic()?
	
	ro_sc = vector3d_sub(ray.o, point3d_to_vector3d(s->coord));
	abc.x = vector3d_dot(ray.d, ray.d);
	abc.y = 2.0 * vector3d_dot(ray.d, ro_sc);
	abc.z = vector3d_dot(ro_sc, ro_sc) - pow(to_double(s->radius), 2.0);
	if (!solve_quadratic(abc, &t, &disc))
		return (dist);
	if (t.x > 0)
	distance = t.x;
	else
	distance = t.y;
	if (distance < 0)
		distance *= -1;
	if (distance < dist)
	{
		rh->coord = vector3d_add(ray.o, vector3d_mult(ray.d, distance));
		rh->color = s->color;
		rh->shape = (t_shape *) s;
		rh->distance = find_distance(ray.o, rh->coord);
		rh->hit = true;
		return (distance);
	}
	return (dist);
}

double	check_pl(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double dist)
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
		if (t < dist)
		{
			if (t > 0)
			{
				rh->color = s->color;
				rh->shape = (t_shape *) s;
				rh->coord = vector3d_add(ray.o, vector3d_mult(ray.d, t));
				rh->distance = t;
				rh->hit = true;
				return (t);
			}
		}
	}
	return (dist);
}

int check_cy(const t_shape *c, const t_Ray r, t_Ray_hit *rh, double *dist)
{
	t_Vector3d dp = vector3d_sub(r.o, point3d_to_vector3d(c->coord));
	t_Vector3d normalized_orientation = vector3d_norm(point3d_to_vector3d(c->orientation));
	t_Vector3d d = vector3d_sub(r.d, vector3d_mult(normalized_orientation, vector3d_dot(r.d, normalized_orientation)));
	t_Vector3d e = vector3d_sub(dp, vector3d_mult(normalized_orientation, vector3d_dot(dp, normalized_orientation)));

	t_Vector3d abc = {vector3d_dot(d, d), 2 * vector3d_dot(d, e), vector3d_dot(e, e) - to_double(c->radius) * to_double(c->radius)};

	double discr = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discr < 0)
		return 0;
	double sqrt_discr = sqrt(discr);
	double t0 = (-abc.y - sqrt_discr) / (2 * abc.x);
	double t1 = (-abc.y + sqrt_discr) / (2 * abc.x);

	if (t0 > t1) {
		double temp = t0;
		t0 = t1;
		t1 = temp;
	}
	t_Vector3d P0 = vector3d_add(r.o, vector3d_mult(r.d, t0));
	t_Vector3d P1 = vector3d_add(r.o, vector3d_mult(r.d, t1));

	t_Vector3d c1 = vector3d_sub(point3d_to_vector3d(c->coord), vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
	t_Vector3d c2 = vector3d_add(point3d_to_vector3d(c->coord), vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));

	double h0 = vector3d_dot(vector3d_sub(P0, c1), vector3d_sub(c2, c1));
	double h1 = vector3d_dot(vector3d_sub(P1, c1), vector3d_sub(c2, c1));

	if (h0 < 0 || h0 > to_double(c->height) * to_double(c->height)) {
		if (h1 < 0 || h1 > to_double(c->height) * to_double(c->height)) {
			return 0; // no intersection
		} else {
			*dist = t1;
			rh->distance = *dist;
			rh->color = c->color;
			rh->shape = (t_shape *)c;
			rh->coord = vector3d_add(r.o, vector3d_mult(r.d, *dist));
			return 1; // intersection at P1
		}
	} else {
		if (h1 < 0) {
			return 0; // no intersection
		} else {
			*dist = t0;
			rh->distance = *dist;
			rh->color = c->color;
			rh->shape = (t_shape *)c;
			rh->coord = vector3d_add(r.o, vector3d_mult(r.d, *dist));
			return 1; // intersection at P0
		}
	}
}

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
				*d = check_pl(s, ray, rh, *d);
			else if (ft_strcmp(s->id, "sp"))
				*d = check_sp(s, ray, rh, *d);
			else if (ft_strcmp(s->id, "cy"))
				check_cy(s, ray, rh, d);
		}
		aff = aff->next;
	}
}
