#include "../../include/miniRT.h"

t_Fixed	str_to_fixed(char *elem)
{
	t_Fixed f;
	set_value(&f, atod(elem));
	return (f);
}

t_3dPoint str_to_3D(char *elem)
{
	t_3dPoint p;
	char **coord = ft_split(elem, ',');
	p.x = str_to_fixed(coord[0]);
	p.y = str_to_fixed(coord[1]);
	p.z = str_to_fixed(coord[2]);
	free_split(coord);
	return (p);
}

double	atod(char *str)
{
	char **nbr = ft_split(str, '.');
	double ret = 0;
	int	negative = 1;
	if (!str)
		return (0);
	if (*str == '-')
		negative = -1;
	ret = (ft_atoi(nbr[0]) * negative);
	if (nbr[1])
		ret += (ft_atoi(nbr[1]) / pow(10, (ft_strlen(nbr[1]))));
	free_split(nbr);
	return (ret * negative);
}