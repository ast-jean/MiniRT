/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:37:03 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/15 23:38:01 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	init_trigger(t_Vars *vars)
{
	vars->x_trigger = 0;
	vars->y_trigger = 0;
	vars->z_trigger = 0;
	vars->radius_trigger = 0;
	vars->camera_trigger = 0;
	vars->orientation_trigger = 0;
	vars->height_trigger = 0;
	vars->FOV_trigger = 0;
	vars->light_trigger = 0;
	vars->ambient_light = 0;
}

t_Vars	*init_vars(void)
{
	static t_Vars	*vars;

	if (!vars)
	{
		vars = malloc(sizeof(t_Vars));
		vars->camera = NULL;
		vars->light = NULL;
		vars->ambient_light = NULL;
		vars->objs = malloc(sizeof(t_dlist));
		vars->objs->first = NULL;
		vars->objs->last = NULL;
		vars->error_message = NULL;
		vars->selected = NULL;
		vars->distance_to_screen = 0;
		vars->i = 0;
		vars->nbr_obj = 0;
		init_trigger(vars);
	}
	return (vars);
}