/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:42:55 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 16:33:35 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

typedef struct s_fixed{
	int	value;
}	t_fixed;

typedef struct s_2dPoint{
	t_fixed	x;
	t_fixed	y;
}	t_2dPoint;

typedef struct s_3dPoint{
	t_fixed	x;
	t_fixed	y;
	t_fixed	z;
}	t_3dPoint;

typedef struct s_rgba{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_rgba;

typedef struct s_rgba_unit{
	double	r;
	double	g;
	double	b;
}	t_rgba_unit;

typedef struct s_shape
{
	char		*id;
	int			index;
	t_fixed		light_ratio;
	uint32_t	color;
	t_3dPoint	orientation;
	int16_t		fov;
	t_3dPoint	coord;
	t_fixed		radius;
	t_fixed		height;
}	t_shape;

#endif
