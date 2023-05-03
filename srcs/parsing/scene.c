#include "../../include/miniRT.h"

void   object_A(char **elem, t_Vars *vars)
{
	if (vars->ambient_light)
		error_exit(3, "Can only be declared once");
	else if (info_count(elem) != 3)
		error_exit(3, "Invalid number of information");
	else
	{
		vars->ambient_light = malloc(sizeof(t_shape));
    	vars->ambient_light->id = "A";
    	vars->ambient_light->light_ratio = parse_light_ratio(elem[1]);
		vars->ambient_light->color = rgb_to_hex(elem[2]);
	}
	if(vars->error_message)
		error_exit(2, "Ambient Light (A): ");
}

void	object_C(char **elem, t_Vars *vars)
{
    if (vars->camera)
		error_exit(3, "Can only be declared once");
	else if (info_count(elem) != 4)
		error_exit(3, "Invalid number of information");
	else
	{
		vars->camera = malloc(sizeof(t_shape));
		vars->camera->id = "C";
		vars->camera->coord = parse_coordinates(elem[1]);
		vars->camera->orientation = parse_orientation(elem[2]);
		vars->camera->FOV = parse_FOV(elem[3]);
		vars->distance_to_screen = (0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
	}
	if(vars->error_message)
		error_exit(2, "Camera (C): ");
}

void	object_L(char **elem, t_Vars *vars)
{
	if (vars->light)
		error_exit(3, "Can only be declared once");
	else if (info_count(elem) != 3 && info_count(elem) != 4)
		error_exit(3, "Invalid number of information");
	else
	{
    	vars->light = malloc(sizeof(t_shape));
		vars->light->id = "L";
		vars->light->coord = parse_coordinates(elem[1]);
		vars->light->light_ratio = parse_light_ratio(elem[2]);
		if (elem[3])
			vars->light->color = rgb_to_hex(elem[3]);
	}
	if(vars->error_message)
		error_exit(2, "Light (L): ");
}

t_Fixed	parse_light_ratio(char *elem)
{
	t_Fixed f;
	double light_ratio = atod(elem);

	if (!is_number(elem) || !range(light_ratio, 0, 1))
		error_exit(2, ft_strjoin("Invalid Light Ratio -> ", elem));
	set_value(&f, light_ratio);
	return (f);
}

t_3dPoint	parse_coordinates(char *elem)
{
	char	**coord = ft_split(elem, ',');
	int i = 0;

	while(coord[i] && is_number(coord[i])
			&& range(atod(coord[i]), INT_MIN, INT_MAX))
		i++;
	if (i != 3)
		error_exit(2, ft_strjoin("Invalid Coordinate -> ", elem));
	free_split(coord);
	return (str_to_3D(elem));
}

t_3dPoint	parse_orientation(char *elem)
{
	char	**coord = ft_split(elem, ',');
	int i = 0;

	while (coord[i] && is_number(coord[i])
			&& range(atod(coord[i]), -1, 1))
		i++;
	if (i != 3)
		error_exit(2, ft_strjoin("Invalid Vector -> ", elem));
	free_split(coord);
	return (str_to_3D(elem));
}

uint8_t parse_FOV(char *elem)
{	
	double fov = atod(elem);
	if (!is_number(elem) || !range(fov, 0, 180))
		error_exit(2, ft_strjoin("Invalid FOV -> ", elem));
	fov = lround(fov);
	return ((uint8_t)fov);
}
