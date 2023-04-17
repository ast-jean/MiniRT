#include "../../include/miniRT.h"

void	free_split(char **args)
{
	int	i = 0;

	if (args)
	while (args[i])
		free(args[i++]);
	if (args)
		free(args);
}

int	range(double elem, int low, int high)
{
	if (elem < low || elem > high)
		return(0);
	return (1);
}

int	char_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return(1);
}

int	is_number(char *str)
{
	int	is_double = 0;

	if (!str)
		return(0);
	if (*str == '-')
		str++;
	while (str && *str)
	{
		if (!char_isdigit(*str))
		{
			if (*str == '.' && !is_double)
				is_double += 1;
			else
				return (0);
		}
		str++;
	}
	return (is_double + 1);
}
