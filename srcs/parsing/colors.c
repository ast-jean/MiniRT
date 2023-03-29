
#include "../../include/miniRT.h"

int	str_is_digit(char *color)
{
	while (*color)
	{
		if (*color < '0' || *color > '9')
			return (0);
		color++;
	}
	return (1);
}

uint8_t	valid_uint8(char *elem, int range)
{
	int	nbr;

	nbr = ft_atoi(elem);
	if ((nbr < 0 || nbr > range) || !str_is_digit(elem))
		error_exit(range, elem);
	return (nbr);
}

uint32_t	rgb_to_hex(char *elem)
{
	char **colors = ft_split(elem, ',');
	int i = 0;
	int bytes = 32;
	uint32_t rgb = 0;
	
	while (colors && colors[i])
		rgb += (valid_uint8(colors[i++], 255) << (bytes -= 8));
	rgb += 255;
	if (!colors || i != 3)
		error_exit(255, elem);
	free_split(colors);
	return(rgb);
}