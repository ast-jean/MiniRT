/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 16:23:21 by slavoie          ###   ########.fr       */
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
		return (rh->hit = true);
	}
	return (false);
}

t_vector2d	find_intersection_dists(t_vector3d abc, double sqrt_discr)
{
	t_vector2d	ts;	

	ts.x = (-abc.y - sqrt_discr) / (2 * abc.x);
	ts.y = (-abc.y + sqrt_discr) / (2 * abc.x);
	swap_quad(&ts);
	return (ts);
}

t_vector2d	calculate_t(const t_shape *c, const t_ray r)
{
	t_vector3d	d;
	t_vector3d	e;
	t_vector3d	abc;
	double		discr;

	calculate_vectors(r, c, &d, &e);
	abc = assign_var_quad(d, e, c);
	discr = abc.y * abc.y - 4 * abc.x * abc.z;
	return (find_intersection_dists(abc, sqrt(discr)));
}

bool	check_cy(t_shape *c, const t_ray r, t_ray_hit *rh, double *dist)
{
	t_vector2d	t;
	t_vector2d	h;
	t_vector3d	p0;
	t_vector3d	p1;

	t = calculate_t(c, r);
	if (t.x < 0 && t.y < 0)
		return (false);
	calculate_intersection_points(r, t, &p0, &p1);
	calculate_heights(c, p0, p1, &h);
	if (h.x < 0 || h.x > to_double(c->height) * to_double(c->height))
	{
		if (h.y >= 0 && h.y <= to_double(c->height) * \
		to_double(c->height) && *dist >= t.y)
			return (check_and_update_intersection((t_shape *)c, r, rh, \
			(*dist = t.y)));
		return (false);
	}
	else
	{
		if ((h.x >= 0 && *dist >= t.x))
			return (check_and_update_intersection((t_shape *)c, \
			r, rh, (*dist = t.x)));
		return (false);
	}
}

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
