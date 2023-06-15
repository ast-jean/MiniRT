/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:05:28 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/15 14:52:14 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <errno.h>

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
		mlx_loop(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	if (vars->error_message)
		printf("Error\n%s\n", vars->error_message);
	mlx_delete_image(vars->mlx, vars->img);
	free_vars(vars);
	return (EXIT_SUCCESS);
}
