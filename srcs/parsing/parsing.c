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
	int		fd =  open(file, O_RDONLY);
	char	c;

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
	t_Vars *vars = init_vars();
	int	fd = open(file, O_RDONLY);
	char *str = ft_gnl(fd);
	char **args;

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

// void	free_split(char **args)
// {
// 	int	i = 0;

// 	if (args)
// 	while (args[i])
// 		free(args[i++]);
// 	if (args)
// 		free(args);
// }

void	valid_element(char **elem)
{
	t_Vars *vars = init_vars();
	if (ft_strcmp(elem[0], "A"))
		object_A(elem, vars);
	else if (ft_strcmp(elem[0], "C"))
		object_C(elem, vars);
	else if (ft_strcmp(elem[0], "L"))
		object_L(elem, vars);
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
