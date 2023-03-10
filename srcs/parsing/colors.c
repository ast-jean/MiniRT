#include "../../include/miniRT.h"

uint32_t RGB_to_hex(char *elem)
{
	char **colors = ft_split(elem, ',');
	uint8_t r = ft_atoi(colors[0]);
	uint8_t g = ft_atoi(colors[1]);
	uint8_t b = ft_atoi(colors[2]);
	uint8_t t = 255;;
	return(r << 24 | g << 16 | b << 8 | t);
}

t_Fixed	str_to_fixed(char *elem)
{
	t_Fixed f;
	char **part = ft_split(elem, '.');
	f.entier = ft_atoi(part[0]);
	if (part[1])
	f.decimal = ft_atoi(part[1]);
	return (f);
}