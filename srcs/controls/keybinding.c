/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:33:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/07 20:09:31 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	are_useful_keys_down(t_vars *vars)
{
	int	useful_keys[28];
	int	num_keys;
	int	i;

	assign_keys_according_to_norm_a(useful_keys);
	assign_keys_according_to_norm_b(useful_keys);
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

void print_info_scene()
{
	t_vars *vars;

	vars = init_vars();
	if (vars->selected)
	{

		printf("OBJECT x = %f y = %f z = %f\n",to_double(vars->selected->coord.x),to_double(vars->selected->coord.y), to_double(vars->selected->coord.z));
		printf("OBJECT_ORIENTATION x = %f y = %f z = %f\n",to_double(vars->selected->orientation.x),to_double(vars->selected->orientation.y), to_double(vars->selected->orientation.z));
	}
	printf("CAMERA x = %f y = %f z = %f\n",to_double(vars->camera->coord.x),to_double(vars->camera->coord.y), to_double(vars->camera->coord.z));
	printf("LIGHT x = %f y = %f z = %f\n",to_double(vars->light->coord.x),to_double(vars->light->coord.y), to_double(vars->light->coord.z));


}

void	process_key_actions(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

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
		ray_to_screen();
		print_info_scene();
	}
}

void	release_mouse_click(t_vars *vars, t_ray *ray, t_ray_hit hit)
{
	t_vector3d	new_coord;
	t_vector3d	hit1;
	t_vector3d	diff;
	double		t;

	*ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
	hit1 = hit.coord;
	diff = vector3d_sub(point3d_to_vector3d(hit.shape->coord), hit1);
	hit = ray_trace(*ray, 999999.9, NULL);
	t = ((hit1.x - ray->o.x) / ray->d.x);
	new_coord.y = (ray->o.y + t * ray->d.y);
	new_coord.z = (ray->o.z + t * ray->d.z);
	new_coord.x = (ray->o.x + t * ray->d.x);
	set_value(&vars->selected->coord.y, new_coord.y + diff.y);
	set_value(&vars->selected->coord.z, new_coord.z + diff.z);
	

}

void	mouse_hook(mouse_key_t button, action_t action, \
modifier_key_t mods, void *param)
{
	t_vars				*vars;
	t_ray				ray;
	static t_ray_hit	hit;

	vars = param;
	mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);
	if ((void)action, (void)mods, mlx_is_mouse_down(vars->mlx, button))
	{
		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray, 999999.9, NULL);
		if (hit.shape)
			vars->selected = hit.shape;
		if (vars->light_trigger)
		{
			set_value(&vars->light->coord.z, hit.coord.z);
			set_value(&vars->light->coord.y, hit.coord.y);
		}
	}
	else
	{
		release_mouse_click(vars, &ray, hit);
		ray_to_screen();
	}
	print_info_scene();
}

void	preset_ambient(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_1))
		vars->ambient_light->color = RED;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_2))
		vars->ambient_light->color = GREEN;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_3))
		vars->ambient_light->color = BLUE;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_4))
		vars->ambient_light->color = GRAY;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_5))
		vars->ambient_light->color = WHITE;
}
