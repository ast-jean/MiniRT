#include "../../include/miniRT.h"

void	error_exit(int code, char *str)
{
	t_Vars *vars = init_vars();
	char *temp;
	
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
	int i = 0;

	while (elem && elem[i] && elem[i][0] != '#')
		i++;
	return(i);
}

void	print_objects()
{
	t_Vars *vars = init_vars();
	t_node *aff = vars->objs->first;
	printf("------------Struct-------------\n");
	printf("ID:\t%s\n", vars->camera->id);
	printf("Coord:\t(%f),(%f),(%f)\n", to_double(vars->camera->coord.x), to_double(vars->camera->coord.y), to_double(vars->camera->coord.z));
    printf("Ori.:\t(%f),(%f),(%f)\n", to_double(vars->camera->orientation.x), to_double(vars->camera->orientation.y), to_double(vars->camera->orientation.z));
    printf("FOV:\t%d\n", vars->camera->FOV);
	printf("-------------------------------\n");
	printf("ID:\t%s\n", vars->ambient_light->id);
	printf("LRatio:\t%f\n", to_double(vars->ambient_light->light_ratio));
	printf("Color:\t%X\n", vars->ambient_light->color);
	printf("-------------------------------\n");
	printf("ID:\t%s\n", vars->light->id);
	printf("Coord:\t(%f),(%f),(%f)\n", to_double(vars->light->coord.x), to_double(vars->light->coord.y), to_double(vars->light->coord.z));
	printf("LRatio:\t%f\n", to_double(vars->light->light_ratio));
	printf("Color:\t%X\n", vars->light->color);
	printf("------------t_dlist------------\n");
	while(aff)
	{
		t_shape *s = aff->content;

		if (ft_strcmp(s->id, "sp")){
			printf("ID:\t%s\n", s->id);
			printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
			printf("Dia.:\t%f\n", to_double(s->radius));
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "pl")){
			printf("ID:\t%s\n", s->id);
            printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
            printf("Ori.:\t(%f),(%f),(%f)\n", to_double(s->orientation.x), to_double(s->orientation.y), to_double(s->orientation.z));
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "cy")){
			printf("ID:\t%s\n", s->id);
            printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
            printf("Ori.:\t(%f),(%f),(%f)\n", to_double(s->orientation.x), to_double(s->orientation.y), to_double(s->orientation.z));
			printf("Dia.:\t%f\n", to_double(s->radius));
			printf("Height:\t%f\n", to_double(s->height));
			printf("Color:\t%X\n", s->color);
		}
		printf("------------------------------\n");
		aff = aff->next;
	}
}
