#include "../../include/miniRT.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}
void	parse(int argc, char **argv)
{
	if (argc != 2)
		error_exit("Bad number of arguments");
	valid_file(argv[1]);
	something(argv[1]);
}

void	valid_file(char *file)
{
	int		fd =  open(file, O_RDONLY);
	char	c;

	if (fd == -1)
		error_exit("File do not exist");
	if (read(fd, &c, 1) == -1)
		error_exit("File is a directory");
	if (!ft_gnl(fd))
		error_exit("File is empty");
	file = ft_strrchr(file, '.');
	if (ft_strncmp(file, ".rt", 4))
		error_exit("Doit être un fichier '.rt'");
	close(fd);
}

void	something(char *file)
{
	int	fd = open(file, O_RDONLY);
	char *str = ft_gnl(fd);
	int i = 0;

	while (str)
	{
		printf("%s\n", str);
		str = ft_gnl(fd);
		i++;
	}
	printf("i = %d\n", i);
}

//A, C, L, sp, pl, cy