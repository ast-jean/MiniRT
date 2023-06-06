/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:45:50 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/04 15:50:29 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	object_a(char **elem, t_vars *vars)
{
	if (vars->ambient_light)
		error_exit(3, "Can only be declared once");
	else if (info_count(elem) != 3)
		error_exit(3, "Invalid number of information");
	else
	{
		vars->ambient_light = malloc(sizeof(t_shape));
		vars->ambient_light->id = "A";
		vars->ambient_light->light_ratio = parse_light_ratio(elem[1]);
		vars->ambient_light->color = rgb_to_hex(elem[2]);
	}
	if (vars->error_message)
		error_exit(2, "Ambient Light (A): ");
}

void	object_c(char **elem, t_vars *vars)
{
	if (vars->camera)
		error_exit(3, "Can only be declared once");
	else if (info_count(elem) != 4)
		error_exit(3, "Invalid number of information");
	else
	{
		vars->camera = malloc(sizeof(t_shape));
		vars->camera->id = "C";
		vars->camera->coord = parse_coordinates(elem[1]);
		vars->camera->orientation = parse_orientation(elem[2]);
		vars->camera->FOV = parse_fov(elem[3]);
		vars->distance_to_screen = (0.5 * WIDTH)
			/ tan(deg2grad(vars->camera->FOV) * 0.5);
	}
	if (vars->error_message)
		error_exit(2, "Camera (C): ");
}

void	object_l(char **elem, t_vars *vars)
{
	if (vars->light)
		error_exit(3, "Can only be declared once");
	else if (info_count(elem) != 3 && info_count(elem) != 4)
		error_exit(3, "Invalid number of information");
	else
	{
		vars->light = malloc(sizeof(t_shape));
		vars->light->id = "L";
		vars->light->coord = parse_coordinates(elem[1]);
		vars->light->light_ratio = parse_light_ratio(elem[2]);
		if (elem[3])
			vars->light->color = rgb_to_hex(elem[3]);
	}
	if (vars->error_message)
		error_exit(2, "Light (L): ");
}
