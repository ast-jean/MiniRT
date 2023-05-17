/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:33:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/17 16:04:48 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	are_useful_keys_down(t_Vars *vars)
{
	int	useful_keys[] =
	{
		61, 334, 333, 45,
		MLX_KEY_PAGE_UP, MLX_KEY_PAGE_DOWN,
		MLX_KEY_UP, MLX_KEY_DOWN,
		MLX_KEY_LEFT, MLX_KEY_RIGHT,
		MLX_KEY_ESCAPE,
		MLX_KEY_1, MLX_KEY_2, MLX_KEY_3,
		MLX_KEY_4, MLX_KEY_5, MLX_KEY_6,
		MLX_KEY_7, MLX_KEY_8,
		MLX_KEY_O, MLX_KEY_X,
		MLX_KEY_Y, MLX_KEY_Z, MLX_KEY_C,
		MLX_KEY_R, MLX_KEY_H,
		MLX_KEY_F, MLX_KEY_L
	};
	int	num_keys;
	int	i;

	i = 0;
	num_keys = sizeof(useful_keys) / sizeof(int);
	while (i < num_keys)
	{
		if (mlx_is_key_down(vars->mlx, useful_keys[i]))
			return (1);
		i++;
	}
	return (0);
}

void	process_key_actions(mlx_key_data_t keydata, void *param)
{
	t_Vars	*vars;

	vars = param;
	(void)keydata;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(vars->mlx);
		return ;
	}
	update_trigger(vars);
	preset_ambient(vars);
	if (are_useful_keys_down(vars))
	{
		check_trigger_xyz(vars);
		check_trigger_orientation(vars);
		change_fov(vars);
		camera_position(vars);
		orient_camera(vars);
		light_x(vars);
		update_ambient_light(vars);
		update_intensity(vars);
		ray_to_screen(vars);
	}
}

void	mouse_hook(mouse_key_t button, action_t action, \
modifier_key_t mods, void *param)
{
	t_Vars		*vars;
	t_Ray		ray;
	t_Ray_hit	hit;

	vars = param;
	(void)action;
	(void)mods;
	if (mlx_is_mouse_down(vars->mlx, button))
	{
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);
		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray, 999999.9, NULL);
		if (hit.shape)
		{
			vars->selected = hit.shape;
			printf("%s selected\n", hit.shape->id);	
		}

		if (vars->light_trigger)
		{
			set_value(&vars->light->coord.z, hit.coord.z);
			set_value(&vars->light->coord.y, hit.coord.y);
		}
	}
	else
	{
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);
		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray, 999999.9, NULL);
		set_value(&vars->selected->coord.z, hit.coord.z);
		set_value(&vars->selected->coord.y, hit.coord.y);
		ray_to_screen();
	}
}

void	preset_ambient(t_Vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_1))
		vars->ambient_light->color = GREEN;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_2))
		vars->ambient_light->color = RED;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_3))
		vars->ambient_light->color = BLUE;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_4))
		vars->ambient_light->color = GRAY;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_5))
		vars->ambient_light->color = WHITE;
}

