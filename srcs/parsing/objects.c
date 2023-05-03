#include "../../include/miniRT.h"

t_shape *object_sp(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	if (info_count(elem) != 4)
		error_exit(3, "Invalid number of information");
	else{
	S->id = "sp";
	S->index = vars->nbr_obj++;
	S->coord = parse_coordinates(elem[1]);
	S->radius = parse_radius(elem[2]);
	S->color = rgb_to_hex(elem[3]);
	}
	if(vars->error_message)
		error_exit(2, "Sphere (sp): ");
	return (S);
}

t_shape *object_pl(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	if (info_count(elem) != 4)
		error_exit(3, "Invalid number of information");
	else{
	S->id = "pl";
	S->index = vars->nbr_obj++; 
	S->coord = parse_coordinates(elem[1]);
	S->orientation = parse_orientation(elem[2]);
	S->color = rgb_to_hex(elem[3]);
	}
	if(vars->error_message)
		error_exit(2, "Plan (pl): ");
	return (S);
}

t_shape *object_cy(char **elem, t_Vars *vars)
{
    t_shape *S = malloc(sizeof(t_shape));
	if (info_count(elem) != 3)
		error_exit(3, "Invalid number of information");
	else{
	S->id = "cy";
	S->index = vars->nbr_obj++; 
	S->coord = parse_coordinates(elem[1]);
	S->orientation = parse_orientation(elem[2]);
	S->radius = parse_radius(elem[3]);
	S->height = parse_size(elem[4]);
	S->color = rgb_to_hex(elem[5]);
	}
	if(vars->error_message)
		error_exit(2, "Cylinder (cy): ");
	return (S);
}

t_Fixed parse_size(char *elem)
{
	t_Fixed f;
	double size = atod(elem);

	if (!is_number(elem) || !range(size, INT_MIN, INT_MAX))
		error_exit(5, ft_strjoin("Invalid Size -> ", elem));
	set_value(&f, size);
	return (f);
}

t_Fixed parse_radius(char *elem)
{
	t_Fixed f;
	double size = atod(elem);

	if (!is_number(elem) || !range(size, INT_MIN, INT_MAX))
		error_exit(5, ft_strjoin("Invalid Size -> ", elem));
	set_value(&f, (size * 0.5));
	return (f);
}

