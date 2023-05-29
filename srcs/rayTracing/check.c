/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/26 17:26:41 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool	check_sp(const t_shape *s, const t_Ray ray, t_Ray_hit *rh, double *dist)
{
	t_Vector3d	abc;
	t_Vector2d	t;
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

t_Vector2d	find_intersection_dists(t_Vector3d abc, double sqrt_discr)
{
	t_Vector2d	ts;	

	ts.x = (-abc.y - sqrt_discr) / (2 * abc.x);
	ts.y = (-abc.y + sqrt_discr) / (2 * abc.x);
	return (ts);
}

bool	check_cy(const t_shape *c, const t_Ray r, t_Ray_hit *rh, double *dist)
{
	t_Vector3d	d;
	t_Vector3d	e;
	t_Vector3d	abc;
	double		discr;
	t_Vector2d	t;
	t_Vector2d	h;
	t_Vector3d	p0;
	t_Vector3d	p1;

	calculate_vectors(r, c, &d, &e);
	abc = assign_var_quad(d, e, c);
	discr = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discr < 0)
		return (false);
	t = find_intersection_dists(abc, sqrt(discr));
	if (t.x < 0 || t.y < 0)
		return (false);
	calculate_intersection_points(r, t, &p0, &p1);
	calculate_heights(c, p0, p1, &h);
	if (h.x < 0 || h.x > to_double(c->height) * to_double(c->height))
		return (check_and_update_intersection((t_shape *)c, r, rh, dist, t.y, \
		(h.y >= 0 && h.y <= to_double(c->height) \
		* to_double(c->height) && *dist >= t.y)));
	else
		return (check_and_update_intersection((t_shape *)c, r, \
		rh, dist, t.x, (h.x >= 0 && *dist >= t.x)));
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
				check_pl(s, ray, rh, d);
			else if (ft_strcmp(s->id, "sp"))
				check_sp(s, ray, rh, d);
			else if (ft_strcmp(s->id, "cy"))
				check_cy(s, ray, rh, d);
		}
		aff = aff->next;
	}
}
