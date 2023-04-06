#include "../../include/miniRT.h"

t_shape *object_sp(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = "sp";
	S->coord = str_to_3D(elem[1]);
	S->radius = atof(elem[2])/2;
	S->color = rgb_to_hex(elem[3]);
	if(vars->error_message)
		error_exit(2, "Sphere (sp): ");
	return (S);
}

t_shape *object_pl(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = "pl";
	S->coord = str_to_3D(elem[1]);
	S->orien = str_to_3D(elem[2]);
	S->color = rgb_to_hex(elem[3]);
	if(vars->error_message)
		error_exit(2, "Plan (pl): ");
	return (S);
}

t_shape *object_cy(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = "cy";
	S->coord = str_to_3D(elem[1]);
	S->orien = str_to_3D(elem[2]);
	S->radius = atof(elem[3])/2.0f;
	S->height = atof(elem[4]);
	S->color = rgb_to_hex(elem[5]);
	if(vars->error_message)
		error_exit(2, "Cylinder (cy): ");
	return (S);
}
