/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:36:55 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/13 13:42:32 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "miniRT.h"

typedef struct s_vars	t_vars;

typedef struct s_vector2d{
	double	x;
	double	y;
}	t_vector2d;

typedef struct s_vector3d{
	double	x;
	double	y;
	double	z;
}	t_vector3d;

typedef struct s_ray{
	t_vector3d	o;
	t_vector3d	d;
}	t_ray;

typedef struct s_ray_hit{
	double		distance;
	uint32_t	color;
	t_shape		*shape;
	t_vector3d	coord;
	t_vector3d	normal;
	bool		hit;
	bool		bounced;
}	t_ray_hit;

/*-------------------------Vectors_ops.c--------------------------*/
t_vector3d	vector3d_add(t_vector3d a, t_vector3d b);
t_vector3d	vector3d_sub(t_vector3d a, t_vector3d b);
t_vector3d	vector3d_mult(t_vector3d v, double b);
t_vector3d	vector3d_mult3d(t_vector3d v, t_vector3d b);
t_vector3d	vector3d_unit(t_vector3d v);
/*-------------------------Vectors.c--------------------------*/
t_vector3d	vector3d_init(double x, double y, double z);
double		vector3d_dot(t_vector3d a, t_vector3d b);
t_vector3d	vector3d_cross(t_vector3d a, t_vector3d b);
double		vector3d_length(t_vector3d v);
t_vector3d	vector3d_norm(const t_vector3d v);
/*-------------------------Ray.c--------------------------*/
t_ray		ray_init(t_vector3d origin, t_vector3d direction);
t_ray		ray_init_to_screen(t_vars *v, int x, int y);
t_vector3d	ray_direction(t_vector3d from, t_vector3d to);

#endif