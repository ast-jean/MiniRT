/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:29:02 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/18 21:03:09 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	update_trigger(t_Vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_O))
		vars->orientation_trigger = !vars->orientation_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_C))
		vars->camera_trigger = !vars->camera_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_X))
		vars->x_trigger = !vars->x_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Y))
		vars->y_trigger = !vars->y_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Z))
		vars->z_trigger = !vars->z_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
		vars->radius_trigger = !vars->radius_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_H))
		vars->height_trigger = !vars->height_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_F))
		vars->FOV_trigger = !vars->FOV_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_L))
		vars->light_trigger = !vars->light_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		vars->ambient_trigger = !vars->ambient_trigger;
	print_trigger_state(vars);
}

void	update_ambient_light(t_Vars *vars)
{
	if (vars->ambient_trigger)
	{
		if ((mlx_is_key_down(vars->mlx, 61) || \
		mlx_is_key_down(vars->mlx, 334)) && \
		(to_double(vars->ambient_light->light_ratio) + 0.1) < 1)
			set_value(&vars->ambient_light->light_ratio, \
			to_double(vars->ambient_light->light_ratio) + 0.1);
		if ((mlx_is_key_down(vars->mlx, 45) || \
		mlx_is_key_down(vars->mlx, 333)) && \
		(to_double(vars->ambient_light->light_ratio) - 0.1) > 0)
			set_value(&vars->ambient_light->light_ratio, \
			to_double(vars->ambient_light->light_ratio) - 0.1);
	}
}

void	update_intensity(t_Vars *vars)
{
	if (vars->light_trigger && vars->radius_trigger)
	{
		if ((mlx_is_key_down(vars->mlx, 61) || \
		mlx_is_key_down(vars->mlx, 334)) && \
		(to_double(vars->light->light_ratio) + 0.1) < 1)
			set_value(&vars->light->light_ratio, \
			to_double(vars->light->light_ratio) + 0.1);
		if ((mlx_is_key_down(vars->mlx, 45) || \
		mlx_is_key_down(vars->mlx, 333)) && \
		(to_double(vars->light->light_ratio) - 0.1) > 0)
			set_value(&vars->light->light_ratio, \
			to_double(vars->light->light_ratio) - 0.1);
	}
}



// void reset_position(t_Fixed *point)
// {
// 	double d = to_double(*point);
	
// 	if (d > 1)
// 		set_value(point, d - 2);
// 	else if (d < -1)
// 		set_value(point, d + 2);
// }



void	reset_position(t_Fixed *point, char c)
{
	// if (to_double(*point) > 1)
	// {
	// 	set_value(point, 1);
	// 	printf("%c = MAX", c);
	// }
	if (to_double(*point) < 0)
	{
		set_value(point, to_double(*point) * -1);
		printf("%c = %f\n", c, to_double(*point));
	}
}
