/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:35:27 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/04 15:50:29 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	check_trigger_xyz_plus(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->selected && vars->radius_trigger)
			vars->selected->radius.value += 50;
		if (vars->selected && vars->height_trigger)
			vars->selected->height.value += 50;
		if (!vars->orientation_trigger)
		{
			if (vars->selected && vars->x_trigger)
				set_value(&vars->selected->coord.x, \
				to_double(vars->selected->coord.x) + 1);
			if (vars->selected && vars->y_trigger)
				set_value(&vars->selected->coord.y, \
				to_double(vars->selected->coord.y) + 1);
			if (vars->selected && vars->z_trigger)
				set_value(&vars->selected->coord.z, \
				to_double(vars->selected->coord.z) + 1);
		}
	}
}

void	check_trigger_xyz(t_vars *vars)
{
	check_trigger_xyz_plus(vars);
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->selected && vars->radius_trigger)
			vars->selected->radius.value -= 50;
		if (vars->selected && vars->height_trigger)
			vars->selected->height.value -= 50;
		if (!vars->orientation_trigger)
		{
			if (vars->selected && vars->x_trigger)
				set_value(&vars->selected->coord.x, \
				to_double(vars->selected->coord.x) - 1);
			if (vars->selected && vars->y_trigger)
				set_value(&vars->selected->coord.y, \
				to_double(vars->selected->coord.y) - 1);
			if (vars->selected && vars->z_trigger)
				set_value(&vars->selected->coord.z, \
				to_double(vars->selected->coord.z) - 1);
		}
	}
}

void	rotate_vector(t_vector3d *vec, double angle, char axis)
{
	double	orig_x;
	double	orig_y;
	double	orig_z;

	angle = angle * (M_PI / 180.0);
	orig_x = vec->x;
	orig_y = vec->y;
	orig_z = vec->z;
	if (axis == 'x' || axis == 'X')
	{
		vec->y = orig_y * cos(angle) - orig_z * sin(angle);
		vec->z = orig_y * sin(angle) + orig_z * cos(angle);
	}
	else if (axis == 'y' || axis == 'Y')
	{
		vec->z = orig_z * cos(angle) - orig_x * sin(angle);
		vec->x = orig_z * sin(angle) + orig_x * cos(angle);
	}
	else if (axis == 'z' || axis == 'Z')
	{
		vec->x = orig_x * cos(angle) - orig_y * sin(angle);
		vec->y = orig_x * sin(angle) + orig_y * cos(angle);
	}
	else
		printf("Invalid rotation axis. Use 'x', 'y', or 'z'.\n");
}

void	check_trigger_orientation(t_vars *vars)
{
	t_vector3d	orientation;
	int			value;

	if (vars->selected)
		orientation = point3d_to_vector3d(vars->selected->orientation);
	else
		return ;
	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
		value = 10;
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
		value = -10;
	if (vars->orientation_trigger && vars->selected)
	{
		if (vars->x_trigger)
			rotate_vector(&orientation, value, 'x');
		if (vars->y_trigger)
			rotate_vector(&orientation, value, 'y');
		if (vars->z_trigger)
			rotate_vector(&orientation, value, 'z');
	}
	if (vars->selected)
		vars->selected->orientation = vec3d_to_point3d(orientation);
}
