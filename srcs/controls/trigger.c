/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:35:27 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/16 11:32:07 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	check_trigger_xyz(t_Vars *vars)
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

void	check_trigger_orientation(t_Vars *vars)
{
	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->orientation_trigger && vars->selected)
		{
			if (vars->x_trigger)
			{
				set_value(&vars->selected->orientation.x, \
				to_double(vars->selected->orientation.x) + 0.1);
				reset_position(&vars->selected->orientation.x);
			}
			if (vars->y_trigger)
			{
				set_value(&vars->selected->orientation.y, \
				to_double(vars->selected->orientation.y) + 0.1);
				reset_position(&vars->selected->orientation.y);
			}
			if (vars->z_trigger)
			{
				set_value(&vars->selected->orientation.z, \
				to_double(vars->selected->orientation.z) + 0.1);
				reset_position(&vars->selected->orientation.z);
			}
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->orientation_trigger && vars->selected)
		{
			if (vars->x_trigger)
			{
				set_value(&vars->selected->orientation.x, \
				to_double(vars->selected->orientation.x) - 0.1);
				reset_position(&vars->selected->orientation.x);
			}
			if (vars->y_trigger)
			{
				set_value(&vars->selected->orientation.y, \
				to_double(vars->selected->orientation.y) - 0.1);
				reset_position(&vars->selected->orientation.y);
			}
			if (vars->z_trigger)
			{
				set_value(&vars->selected->orientation.z, \
				to_double(vars->selected->orientation.z) - 0.1);
				reset_position(&vars->selected->orientation.z);
			}
		}
	}
}