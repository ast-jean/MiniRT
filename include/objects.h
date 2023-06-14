/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:42:55 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/13 13:46:55 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

typedef struct s_Fixed{
	int	value;
}	t_Fixed;

typedef struct s_2dPoint{
	t_Fixed	x;
	t_Fixed	y;
}	t_2dPoint;

typedef struct s_3dPoint{
	t_Fixed	x;
	t_Fixed	y;
	t_Fixed	z;
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
	t_Fixed		light_ratio;
	uint32_t	color;
	t_3dPoint	orientation;
	int16_t		fov;
	t_3dPoint	coord;
	t_Fixed		radius;
	t_Fixed		height;
}	t_shape;

#endif
