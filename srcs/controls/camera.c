/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:40:12 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/08 14:19:27 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	change_fov(t_vars *vars)
{
	if (vars->fov_trigger)
	{
		if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
		{
			if ((int)vars->camera->FOV <= (int)180)
			{
				vars->camera->FOV = clamp(vars->camera->FOV + 3, 0, 180);
				vars->distance_to_screen = \
				(0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
			}
		}
		if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
		{
			if (vars->camera->FOV >= 0)
			{
				vars->camera->FOV = clamp(vars->camera->FOV - 3, 0, 180);
				vars->distance_to_screen = \
				(0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
			}
		}
		
	}
}

void	camera_position_plus(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->camera_trigger && !vars->orientation_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->coord.x, \
				to_double(vars->camera->coord.x) + 10);
			if (vars->y_trigger)
				set_value(&vars->camera->coord.y, \
				to_double(vars->camera->coord.y) + 10);
			if (vars->z_trigger)
				set_value(&vars->camera->coord.z, \
				to_double(vars->camera->coord.z) + 10);
		}
	}
}

void	camera_position(t_vars *vars)
{
	camera_position_plus(vars);
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->camera_trigger && !vars->orientation_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->coord.x, \
				to_double(vars->camera->coord.x) - 10);
			if (vars->y_trigger)
				set_value(&vars->camera->coord.y, \
				to_double(vars->camera->coord.y) - 10);
			if (vars->z_trigger)
				set_value(&vars->camera->coord.z, \
				to_double(vars->camera->coord.z) - 10);
		}
	}
	
}

void	orient_camera_plus(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->camera_trigger && vars->orientation_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->orientation.x, \
				to_double(vars->camera->orientation.x) + 0.007);
			if (vars->y_trigger)
				set_value(&vars->camera->orientation.y, \
				to_double(vars->camera->orientation.y) + 0.007);
			if (vars->z_trigger)
				set_value(&vars->camera->orientation.z, \
				to_double(vars->camera->orientation.z) + 0.007);
		}
	}
}

void	orient_camera(t_vars *vars)
{
	orient_camera_plus(vars);
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->camera_trigger && vars->orientation_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->orientation.x, \
				to_double(vars->camera->orientation.x) - 0.007);
			if (vars->y_trigger)
				set_value(&vars->camera->orientation.y, \
				to_double(vars->camera->orientation.y) - 0.007);
			if (vars->z_trigger)
				set_value(&vars->camera->orientation.z, \
				to_double(vars->camera->orientation.z) - 0.007);
		}
	}
}
