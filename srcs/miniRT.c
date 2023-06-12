/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:05:28 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/12 11:43:48 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <errno.h>

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
}

void	free_vars(t_vars *vars)
{
	dlist_free_content(vars->objs);
	free(vars->objs);
	free(vars->ambient_light);
	free(vars->light);
	free(vars->camera);
	if (vars->error_message)
		free(vars->error_message);
	free(vars);
}

void	print_trigger_state(t_vars *vars)
{
	printf("\033[32m");
	printf(" -------------------\n");
	printf("|Active trigger     |\n");
	printf("|R=%d, H=%d, O=%d, F=%d |\n|C=%d,\
 X=%d, Y=%d, Z=%d |\n|L=%d, A=%d, I=%d	    |\n", \
	vars->radius_trigger, vars->height_trigger, vars->orientation_trigger, \
	vars->fov_trigger, vars->camera_trigger, vars->x_trigger, \
	vars->y_trigger, vars->z_trigger, vars->light_trigger, \
	vars->ambient_trigger, vars->interface_trigger);
	printf(" -------------------\n");
	printf("\033[0m\n");
}

void	light_x(t_vars *vars)
{
	if (vars->light_trigger && !vars->radius_trigger)
	{
		if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
			set_value(&vars->light->coord.x, \
			to_double(vars->light->coord.x) + 5);
		if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
			set_value(&vars->light->coord.x, \
			to_double(vars->light->coord.x) - 5);
	}
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	vars = init_vars();
	parse(argc, argv);
	if (!vars->error_message)
	{
		vars->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
		vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		ray_to_screen();
		mlx_mouse_hook(vars->mlx, mouse_hook, vars);
		mlx_key_hook(vars->mlx, process_key_actions, vars);
		mlx_loop_hook(vars->mlx, &hook, vars);
		mlx_loop(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	if (!vars->error_message)
		printf("\n\nGOOD\n\n");
	else
		printf("Error\n%s\n", vars->error_message);
	free_vars(vars);
	return (EXIT_SUCCESS);
}
