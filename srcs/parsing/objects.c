/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:44:05 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/15 14:25:50 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_shape	*object_sp(char **elem, t_vars *vars)
{
	t_shape		*s;

	s = NULL;
	if (info_count(elem) != 4)
		error_exit(3, "Invalid number of information", false);
	else
	{
		s = malloc(sizeof(t_shape));
		s->id = "sp";
		s->index = vars->nbr_obj++;
		s->coord = parse_coordinates(elem[1]);
		s->radius = parse_radius(elem[2]);
		s->color = rgb_to_hex(elem[3]);
	}
	if (vars->error_message)
		error_exit(2, "sphere (sp): ", false);
	return (s);
}

t_shape	*object_pl(char **elem, t_vars *vars)
{
	t_shape		*s;

	s = NULL;
	if (info_count(elem) != 4)
		error_exit(3, "Invalid number of information", false);
	else
	{
		s = malloc(sizeof(t_shape));
		s->id = "pl";
		s->index = vars->nbr_obj++;
		s->coord = parse_coordinates(elem[1]);
		s->orientation = parse_orientation(elem[2]);
		s->color = rgb_to_hex(elem[3]);
	}
	if (vars->error_message)
		error_exit(2, "Plan (pl): ", false);
	return (s);
}

t_shape	*object_cy(char **elem, t_vars *vars)
{
	t_shape		*s;
	t_vector3d	orientation;

	s = NULL;
	if (info_count(elem) != 6)
		error_exit(3, "Invalid number of information", false);
	else
	{
		s = malloc(sizeof(t_shape));
		s->id = "cy";
		s->index = vars->nbr_obj++;
		s->coord = parse_coordinates(elem[1]);
		s->orientation = parse_orientation(elem[2]);
		s->radius = parse_radius(elem[3]);
		s->height = parse_size(elem[4]);
		s->color = rgb_to_hex(elem[5]);
		orientation = point3d_to_vector3d(s->orientation);
		reset_position(&orientation);
		s->orientation = vec3d_to_point3d(orientation);
	}
	if (vars->error_message)
		error_exit(2, "Cylinder (cy): ", false);
	return (s);
}

t_fixed	parse_size(char *elem)
{
	t_fixed	f;
	double	size;

	size = atod(elem);
	if (!is_number(elem) || !range(size, INT_MIN, INT_MAX))
		error_exit(5, ft_strjoin("Invalid size -> ", elem), true);
	set_value(&f, size);
	return (f);
}

t_fixed	parse_radius(char *elem)
{
	t_fixed	f;
	double	size;

	size = atod(elem);
	if (!is_number(elem) || !range(size, INT_MIN, INT_MAX))
		error_exit(5, ft_strjoin("Invalid size -> ", elem), true);
	set_value(&f, (size * 0.5));
	return (f);
}
