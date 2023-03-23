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
	vars->camera->FOV = ft_atoi(elem[3]);

	t_Vector3d c_coords = Point3d_to_Vector3d(vars->camera->coord);
	t_Vector3d c_dir = Point3d_to_Vector3d(vars->camera->orientation);
	
	
	t_Vector3d pc = Vector3d_add(c_coords, Vector3d_mult(c_dir, vars->camera->FOV));  
	//pc = c_coords + (c_dir * FOV)
	
	t_Vector3d pdx = Vector3d_unit(Vector3d_cross(c_dir, Vector3d_init(0.0, -1.0, 0.0)));
	//pdx = unit(cross(c_dir, {0,-1,0}))
	
	t_Vector3d pdy = Vector3d_cross(Vector3d_mult(c_dir, -1.0), c_coords);
	//pdy = cross(c_dir * -1), c_coord)


	*vars->planeCenter = pc;
	*vars->planeDirectionX = pdx;
	*vars->planeDirectionY = pdy;

	// printf("pc.x = %f |pc.y = %f|pc.z = %f|\n", vars->planeCenter->x, vars->planeCenter->y, vars->planeCenter->z);
	// printf("pdx.x = %f |pdx.y = %f|pdx.z = %f|\n", vars->planeDirectionX->x, vars->planeDirectionX->y, vars->planeDirectionX->z);
	// printf("pdy.x = %f |pdy.y = %f|pdy.z = %f|\n", vars->planeDirectionY->x, vars->planeDirectionY->y, vars->planeDirectionY->z);


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