#include "../../include/miniRT.h"

void   object_A(char **elem, t_Vars *vars)
{
	if (vars->ambient_light)
		error_exit(3, "Can only be declared once");
	else
	{
		vars->ambient_light = malloc(sizeof(t_shape));
    	vars->ambient_light->id = "A";
    	vars->ambient_light->light_ratio = atof(elem[1]) * 100;
		vars->ambient_light->color = rgb_to_hex(elem[2]);
	}
	if(vars->error_message)
		error_exit(2, "Ambient Light (A): ");
}

void	object_C(char **elem, t_Vars *vars)
{
    if (vars->camera)
		error_exit(3, "Can only be declared once");
	else
	{
		vars->camera = malloc(sizeof(t_shape));
		vars->camera->id = "C";
		vars->camera->coord = str_to_3D(elem[1]);
		vars->camera->orien = str_to_3D(elem[2]);
		vars->camera->FOV = valid_uint8(elem[3], 180);
		vars->distance_to_screen = (0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
		printf("distance_to_screen = %f\n", vars->distance_to_screen);
	}
	if(vars->error_message)
		error_exit(2, "Camera (C): ");
}

void	object_L(char **elem, t_Vars *vars)
{
	if (vars->light)
		error_exit(3, "Can only be declared once");
	else
	{
    	vars->light = malloc(sizeof(t_shape));
		vars->light->id = "L";
		vars->light->coord = str_to_3D(elem[1]);
		vars->light->light_ratio = atof(elem[2]) * 100;
		if (elem[3])
			vars->light->color = rgb_to_hex(elem[3]);
	}
	if(vars->error_message)
		error_exit(2, "Light (L): ");
}