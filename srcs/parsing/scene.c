#include "../../include/miniRT.h"

void   object_A(char **elem, t_Vars *vars)
{
	if (vars->ambient_light)
		return(error_exit(2, "Object 'A' can only be declared once"));
	vars->ambient_light = malloc(sizeof(t_shape));
    vars->ambient_light->id = "A";
    vars->ambient_light->light_ratio = str_to_fixed(elem[1]);
	vars->ambient_light->color = RGB_to_hex(elem[2]);
}

void	object_C(char **elem, t_Vars *vars)
{
    if (vars->camera)
		return(error_exit(2, "Object 'C' can only be declared once"));
	vars->camera = malloc(sizeof(t_shape));
	vars->camera->id = "C";
	vars->camera->coord = str_to_3D(elem[1]);
	vars->camera->orientation = str_to_3D(elem[2]);
	vars->camera->FOV = atoi(elem[3]);
	// vars->distance_to_screen = 0.5 * HEIGHT / tan(0.5 * vars->camera->FOV);
	vars->distance_to_screen = (0.5 * WIDTH) / tan((vars->camera->FOV * (M_PI / 180.0)) * 0.5);
	printf("distance_to_screen = %f\n", vars->distance_to_screen);
}

void	object_L(char **elem, t_Vars *vars)
{
	if (vars->light)
		return(error_exit(2, "Object 'L' can only be declared once"));
    vars->light = malloc(sizeof(t_shape));
	vars->light->id = "L";
	vars->light->coord = str_to_3D(elem[1]);
	vars->light->light_ratio = str_to_fixed(elem[2]);
	if (elem[3])
		vars->light->color = RGB_to_hex(elem[3]);
}