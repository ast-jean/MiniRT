#include "../../include/miniRT.h"

void	error_exit(int code, char *str)
{
	t_Vars *vars = init_vars();
	
	printf("%s\n", str);
	if (code == 1)
		exit(0);
	if (code == 2)
		vars->error_message = 1;
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
			printf("Dia.:\t%f\n", to_double(s->diameter));
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
			printf("Dia.:\t%f\n", to_double(s->diameter));
			printf("Height:\t%f\n", to_double(s->height));
			printf("Color:\t%X\n", s->color);
		}
		printf("------------------------------\n");
		aff = aff->next;
	}
}

		// if (ft_strcmp(s->id, "A")){
		// 	printf("ID:\t%s\n", s->id);
		// 	printf("LRatio:\t%f\n", to_double(s->light_ratio));
		// 	printf("Color:\t%X\n", s->color);
		// }
		// else if (ft_strcmp(s->id, "C")){
		// 	printf("ID:\t%s\n", s->id);
		// 	printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
        //     printf("Ori.:\t(%f),(%f),(%f)\n", to_double(s->orientation.x), to_double(s->orientation.y), to_double(s->orientation.z));
        //     printf("FOV:\t%d\n", s->FOV);
		// }
		// else if (ft_strcmp(s->id, "L")){
		// 	printf("ID:\t%s\n", s->id);
		// 	printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
		// 	printf("LRatio:\t%f\n", to_double(s->light_ratio));
		// 	printf("Color:\t%X\n", s->color);
		// }

// void	print_objects(t_dlist *l)
// {
// 	t_node *aff = l->first;

// 	while(aff)
// 	{
// 		t_shape *s = aff->content;

// 		if (ft_strcmp(s->id, "A")){
// 			printf("ID:\t%s\n", s->id);
// 			printf("LRatio:\t%d,%d\n", s->light_ratio.entier, s->light_ratio.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "C")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
//             printf("Ori.:\t%d.%d,", s->orientation.x.entier, s->orientation.x.decimal);
//             printf("%d.%d,", s->orientation.y.entier, s->orientation.y.decimal);
//             printf("%d.%d\n", s->orientation.z.entier, s->orientation.z.decimal);
//             printf("FOV:\t%d\n", s->FOV);
// 		}
// 		else if (ft_strcmp(s->id, "L")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
// 			printf("LRatio:\t%d,%d\n", s->light_ratio.entier, s->light_ratio.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "sp")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
// 			printf("Dia.:\t%d,%d\n", s->diameter.entier, s->diameter.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "pl")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
//             printf("Ori.:\t%d.%d,", s->orientation.x.entier, s->orientation.x.decimal);
//             printf("%d.%d,", s->orientation.y.entier, s->orientation.y.decimal);
//             printf("%d.%d\n", s->orientation.z.entier, s->orientation.z.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "cy")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
//             printf("Ori.:\t%d.%d,", s->orientation.x.entier, s->orientation.x.decimal);
//             printf("%d.%d,", s->orientation.y.entier, s->orientation.y.decimal);
//             printf("%d.%d\n", s->orientation.z.entier, s->orientation.z.decimal);
// 			printf("Dia.:\t%d,%d\n", s->diameter.entier, s->diameter.decimal);
// 			printf("Height:\t%d,%d\n", s->height.entier, s->height.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		printf("------------------------------\n");
// 		aff = aff->next;
// 	}

// }
