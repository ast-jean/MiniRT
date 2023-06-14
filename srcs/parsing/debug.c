/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:33:14 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/14 09:12:57 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	error_exit(int code, char *str)
{
	t_vars	*vars;
	char	*temp;

	vars = init_vars();
	if (code == 1)
	{
		printf("Error\n%s", str);
		free_vars(vars);
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
	if (code == 5)
	{
		if (!vars->error_message)
			vars->error_message = ft_strjoin(str, vars->error_message);
		free(str);
	}
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
		printf("OBJECT x = %f y = %f z = %f\n", \
		to_double(vars->selected->coord.x), \
		to_double(vars->selected->coord.y), \
		to_double(vars->selected->coord.z));
		printf("OBJECT_ORIENTATION x = %f y = %f z = %f\n", \
		to_double(vars->selected->orientation.x), \
		to_double(vars->selected->orientation.y), \
		to_double(vars->selected->orientation.z));
	}
	printf("CAMERA x = %f y = %f z = %f\n", \
	to_double(vars->camera->coord.x), \
	to_double(vars->camera->coord.y), to_double(vars->camera->coord.z));
	printf("LIGHT x = %f y = %f z = %f\n", \
	to_double(vars->light->coord.x), \
	to_double(vars->light->coord.y), to_double(vars->light->coord.z));
}
