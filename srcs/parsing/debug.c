#include "../../include/miniRT.h"
// #pragma once

void	error_exit(int code, char *str)
{
	t_Vars	*vars;
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
/*
2 = free old message, join new part in front of it
3 = New error message
5 = new error message free str
*/

int	info_count(char **elem)
{
	int	i;

	i = 0;
	while (elem && elem[i] && elem[i][0] != '#')
		i++;
	return (i);
}
