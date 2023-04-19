#include "../../include/miniRT.h"

t_shape *object_sp(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = "sp";
	S->index = vars->nbr_obj++;
	S->coord = parse_coordinates(elem[1]);
	S->radius = fp_init(fp_cal('/', 2, str_to_fixed(elem[2]), fp_init(2)));
	S->color = rgb_to_hex(elem[3]);
	if(vars->error_message)
		error_exit(2, "Sphere (sp): ");
	return (S);
}

t_shape *object_pl(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = "pl";
	S->index = vars->nbr_obj++; 
	S->coord = parse_coordinates(elem[1]);
	S->orientation = parse_orientation(elem[2]);
	S->color = rgb_to_hex(elem[3]);
	if(vars->error_message)
		error_exit(2, "Plan (pl): ");
	return (S);
}

t_shape *object_cy(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = "cy";
	S->index = vars->nbr_obj++; 
	S->coord = parse_coordinates(elem[1]);
	S->orientation = parse_orientation(elem[2]);
	S->radius = fp_init(fp_cal('/', 2, str_to_fixed(elem[2]), fp_init(2)));
	S->height = str_to_fixed(elem[4]);
	S->color = rgb_to_hex(elem[5]);
	if(vars->error_message)
		error_exit(2, "Cylinder (cy): ");
	return (S);
}

