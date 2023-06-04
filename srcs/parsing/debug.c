/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:33:14 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/04 15:50:29 by ast-jean         ###   ########.fr       */
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
