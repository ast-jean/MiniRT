#include "../../include/miniRT.h"

uint32_t RGB_to_hex(char *elem)
{
	char **colors = ft_split(elem, ',');
	int r = ft_atoi(colors[0]);
	int g = ft_atoi(colors[1]);
	int b = ft_atoi(colors[2]);
	int t = 255;;
	return(r << 24 | g << 16 | b << 8 | t);
}
