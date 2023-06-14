/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/12 15:40:35 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	calculate_vectors(const t_ray r, \
const t_shape *c, t_vector3d *d, t_vector3d *e)
{
	t_vector3d	dp;
	t_vector3d	no;

	dp = vector3d_sub(r.o, point3d_to_vector3d(c->coord));
	no = vector3d_norm(point3d_to_vector3d(c->orientation));
	*d = vector3d_sub(r.d, vector3d_mult(no, vector3d_dot(r.d, no)));
	*e = vector3d_sub(dp, vector3d_mult(no, vector3d_dot(dp, no)));
}

void	calculate_intersection_points(const t_ray r, t_vector2d t, \
t_vector3d *P0, t_vector3d *P1)
{
	*P0 = vector3d_add(r.o, vector3d_mult(r.d, t.x));
	*P1 = vector3d_add(r.o, vector3d_mult(r.d, t.y));
}

void	calculate_heights(const t_shape *c, \
t_vector3d P0, t_vector3d P1, t_vector2d *h)
{
	t_vector3d	normalized_orientation;
	t_vector3d	c1;
	t_vector3d	c2;

	normalized_orientation = vector3d_norm(point3d_to_vector3d(c->orientation));
	c1 = vector3d_sub(point3d_to_vector3d(c->coord), \
	vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
	c2 = vector3d_add(point3d_to_vector3d(c->coord), \
	vector3d_mult(normalized_orientation, to_double(c->height) / 2.0));
	h->x = vector3d_dot(vector3d_sub(P0, c1), vector3d_sub(c2, c1));
	h->y = vector3d_dot(vector3d_sub(P1, c1), vector3d_sub(c2, c1));
}

bool	check_and_update_intersection(t_shape *c, const t_ray r, \
t_ray_hit *rh, double dist)
{
	rh->distance = dist;
	rh->color = c->color;
	rh->shape = (t_shape *)c;
	rh->hit = true;
	rh->coord = vector3d_add(r.o, vector3d_mult(r.d, dist));
	return (true);
}
