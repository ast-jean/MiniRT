/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:57:17 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/04 15:50:29 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	parse(int argc, char **argv)
{
	if (argc != 2)
		error_exit(1, "Wrong number of arguments\n");
	valid_file(argv[1]);
	split(argv[1]);
	valid_scene();
}

void	valid_file(char *file)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(1, "File do not exist\n");
	if (read(fd, &c, 1) == -1)
		error_exit(1, "File is a directory\n");
	if (!ft_gnl(fd))
		error_exit(1, "File is empty\n");
	file = ft_strrchr(file, '.');
	if (ft_strncmp(file, ".rt", 4))
		error_exit(1, "Must be a '.rt' type of file\n");
	close(fd);
}

void	split(char *file)
{
	t_vars	*vars;
	int		fd;
	char	*str;
	char	**args;

	vars = init_vars();
	fd = open(file, O_RDONLY);
	str = ft_gnl(fd);
	while (str && !vars->error_message)
	{
		args = ft_split(str, ' ');
		valid_element(args);
		str = ft_gnl(fd);
		if (vars->error_message)
			free(str);
	}
	close(fd);
}

void	valid_element(char **elem)
{
	t_vars	*vars;

	vars = init_vars();
	if (ft_strcmp(elem[0], "A"))
		object_a(elem, vars);
	else if (ft_strcmp(elem[0], "C"))
		object_c(elem, vars);
	else if (ft_strcmp(elem[0], "L"))
		object_l(elem, vars);
	else if (ft_strcmp(elem[0], "sp"))
		dlist_add_back(vars->objs, object_sp(elem, vars));
	else if (ft_strcmp(elem[0], "pl"))
		dlist_add_back(vars->objs, object_pl(elem, vars));
	else if (ft_strcmp(elem[0], "cy"))
		dlist_add_back(vars->objs, object_cy(elem, vars));
	else if (!ft_strcmp(elem[0], "#"))
		error_exit(5, ft_strjoin("Invalid element: ", elem[0]));
	free_split(elem);
}
