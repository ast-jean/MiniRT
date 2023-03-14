#include "../../include/miniRT.h"

int	RGB_digit(char *color)
{
	while (*color)
	{
		if (*color < '0' || *color > '9')
			return (0);
		color++;
	}
	return (1);
}

uint8_t valid_RGB(char *color)
{
	int RGB = ft_atoi(color);
	if ((RGB < 0 || RGB > 255) || !RGB_digit(color))
		error_exit("Invalid RGB");
	return (RGB);
}

uint32_t RGB_to_hex(char *elem)
{
	char **colors = ft_split(elem, ',');
	uint8_t r = valid_RGB(colors[0]);
	uint8_t g = valid_RGB(colors[1]);
	uint8_t b = valid_RGB(colors[2]);
	uint8_t t = 255;
	free_split(colors);
	return(r << 24 | g << 16 | b << 8 | t);
}
