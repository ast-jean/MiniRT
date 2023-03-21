#include "../../include/miniRT.h"

void   object_A(char **elem, t_Vars *vars)
{
	if (vars->ambient_light)
		error_exit("Object 'A' can only be declared once");
	vars->ambient_light = malloc(sizeof(t_shape));
    vars->ambient_light->id = "A";
    vars->ambient_light->light_ratio = str_to_fixed(elem[1]);
	vars->ambient_light->color = RGB_to_hex(elem[2]);
}

void	object_C(char **elem, t_Vars *vars)
{
    if (vars->camera)
		error_exit("Object 'C' can only be declared once");
	vars->camera = malloc(sizeof(t_shape));
	vars->camera->id = "C";
	vars->camera->coord = str_to_3D(elem[1]);
	vars->camera->orientation = str_to_3D(elem[2]);
	vars->camera->FOV = ft_atoi(elem[3]);

	t_Vector3d c_coords = Point3d_to_Vector3d(vars->camera->coord);
	t_Vector3d c_dir = Point3d_to_Vector3d(vars->camera->orientation);

    vars->planeCenter = Vector3d_add(c_coords, Vector3d_mult(c_dir, vars->camera->FOV));  
	vars->planeDirectionX = Vector3d_unit(Vector3d_cross(c_dir, Vector3d_init(0.0, -1.0, 0.0)));
	vars->planeDirectionY = Vector3d_cross(Vector3d_mult(c_dir, -1.0), c_coords);
}

void	object_L(char **elem, t_Vars *vars)
{
	if (vars->light)
		error_exit("Object 'L' can only be declared once");
    vars->light = malloc(sizeof(t_shape));
	vars->light->id = "L";
	vars->light->coord = str_to_3D(elem[1]);
	vars->light->light_ratio = str_to_fixed(elem[2]);
	if (elem[3])
		vars->light->color = RGB_to_hex(elem[3]);
}