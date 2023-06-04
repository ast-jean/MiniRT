/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:24:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/04 15:39:45 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	assign_var_pl(t_ray_hit *rh, \
const t_shape *s, const t_ray ray, double t)
{
	rh->color = s->color;
	rh->shape = (t_shape *) s;
	rh->coord = vector3d_add(ray.o, vector3d_mult(ray.d, t));
	rh->distance = t;
	rh->hit = true;
}

bool	check_pl(const t_shape *s, const t_ray ray, t_ray_hit *rh, double *dist)
{
	t_vector3d	sc;
	t_vector3d	so;
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
				assign_var_pl(rh, s, ray, t);
				return (true);
			}
		}
	}
	return (false);
}
