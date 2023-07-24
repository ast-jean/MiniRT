/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:33:14 by ast-jean          #+#    #+#             */
/*   Updated: 2023/07/24 14:06:46 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	error_exit(int code, char *str, bool alloc)
{
	t_vars	*vars;
	char	*temp;

	vars = init_vars();
	if (code == 1)
	{
		printf("Error\n%s", str);
		free_vars(vars);
		if (alloc)
			free(str);
		exit(0);
	}
	if (code == 2)
	{
		temp = vars->error_message;
		vars->error_message = ft_strjoin(str, vars->error_message);
		free(temp);
	}
	if (code == 3 && !vars->error_message)
		vars->error_message = ft_strjoin(str, vars->error_message);
	if (alloc)
		free(str);
}

int	info_count(char **elem)
{
	int	i;

	i = 0;
	while (elem && elem[i] && elem[i][0] != '#')
	{
		i++;
	}		
	return (i);
}

void	print_info_scene(void)
{
	t_vars	*vars;

	vars = init_vars();

	if (vars->selected)
	{
		t_rgba obj_rgb = separate_color_rgba(vars->selected->color);
		if(ft_strcmp(vars->selected->id, "cy"))
		{
			printf("%s	%f,%f,%f	%f,%f,%f	%f	%f	%u,%u,%u\n", vars->selected->id,to_double(vars->selected->coord.x), \
			to_double(vars->selected->coord.y), to_double(vars->selected->coord.z), to_double(vars->selected->orientation.x), \
			to_double(vars->selected->orientation.y), to_double(vars->selected->orientation.z), to_double(vars->selected->radius) * 2, to_double(vars->selected->height), \
			obj_rgb.r, obj_rgb.g, obj_rgb.b);
		}
		if(ft_strcmp(vars->selected->id, "pl"))
		{
			printf("%s	%f,%f,%f	%f,%f,%f	%u,%u,%u\n", vars->selected->id,to_double(vars->selected->coord.x), \
			to_double(vars->selected->coord.y), to_double(vars->selected->coord.z), to_double(vars->selected->orientation.x), \
			to_double(vars->selected->orientation.y), to_double(vars->selected->orientation.z), obj_rgb.r, obj_rgb.g, obj_rgb.b);
		}
		if(ft_strcmp(vars->selected->id, "sp"))
		{
			printf("%s	%f,%f,%f	%f	%u,%u,%u\n", vars->selected->id,to_double(vars->selected->coord.x), \
			to_double(vars->selected->coord.y), to_double(vars->selected->coord.z), to_double(vars->selected->radius) * 2, obj_rgb.r, obj_rgb.g, obj_rgb.b);
		}
	}
	t_rgba	light_rgb = separate_color_rgba(vars->light->color);
	t_rgba	ambient_rgb = separate_color_rgba(vars->ambient_light->color);

	printf("%s	%f,%f,%f	%d\n", vars->camera->id, to_double(vars->camera->coord.x), to_double(vars->camera->coord.y), to_double(vars->camera->coord.z), vars->camera->fov);
	printf("%s	%f,%f,%f	%f	%u,%u,%u\n", vars->light->id, to_double(vars->light->coord.x), to_double(vars->light->coord.y), to_double(vars->light->coord.z), to_double(vars->light->light_ratio), light_rgb.r, light_rgb.g, light_rgb.b);
	printf("%s	%f	%u,%u,%u\n", vars->ambient_light->id, to_double(vars->ambient_light->light_ratio), ambient_rgb.r, ambient_rgb.g, ambient_rgb.b);
}
