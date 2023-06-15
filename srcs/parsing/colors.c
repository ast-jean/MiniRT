/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:39:34 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/15 14:22:33 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

uint8_t	valid_uint8(char *elem)
{
	int	nbr;

	nbr = ft_atoi(elem);
	if ((nbr < 0 || nbr > 255) || is_number(elem) != 1)
		error_exit(5, ft_strjoin("Invalid RGB -> ", elem), true);
	return (nbr);
}

uint32_t	rgb_to_hex(char *elem)
{
	char		**colors;
	int			i;
	int			bytes;
	uint32_t	rgb;

	colors = ft_split(elem, ',');
	i = 0;
	bytes = 32;
	rgb = 0;
	while (colors && colors[i])
		rgb += (valid_uint8(colors[i++]) << (bytes -= 8));
	rgb += 255;
	if (!colors || i != 3)
		error_exit(5, ft_strjoin("Invalid RGB -> ", elem), true);
	free_split(colors);
	return (rgb);
}
