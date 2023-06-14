/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:51:27 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 16:34:58 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_fixed	parse_light_ratio(char *elem)
{
	t_fixed	f;
	double	light_ratio;

	light_ratio = atod(elem);
	if (!is_number(elem) || !range(light_ratio, 0, 1))
		error_exit(2, ft_strjoin("Invalid Light Ratio -> ", elem));
	set_value(&f, light_ratio);
	return (f);
}

t_3dPoint	parse_coordinates(char *elem)
{
	char	**coord;
	int		i;

	coord = ft_split(elem, ',');
	i = 0;
	while (coord[i] && is_number(coord[i])
		&& range(atod(coord[i]), INT_MIN, INT_MAX))
		i++;
	if (i != 3)
		error_exit(2, ft_strjoin("Invalid Coordinate -> ", elem));
	free_split(coord);
	return (str_to_3d(elem));
}

t_3dPoint	parse_orientation(char *elem)
{
	char	**coord;
	int		i;

	coord = ft_split(elem, ',');
	i = 0;
	while (coord[i] && is_number(coord[i])
		&& range(atod(coord[i]), -1, 1))
		i++;
	if (i != 3)
		error_exit(2, ft_strjoin("Invalid Vector -> ", elem));
	free_split(coord);
	return (str_to_3d(elem));
}

uint8_t	parse_fov(char *elem)
{	
	double	fov;

	fov = atod(elem);
	if (!is_number(elem) || !range(fov, 0, 180))
		error_exit(2, ft_strjoin("Invalid fov -> ", elem));
	fov = lround(fov);
	return ((uint8_t)fov);
}
