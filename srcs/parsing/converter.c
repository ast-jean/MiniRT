/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:39:47 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/14 16:33:56 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_fixed	str_to_fixed(char *elem)
{
	t_fixed	f;

	set_value(&f, atod(elem));
	return (f);
}

t_3dPoint	str_to_3d(char *elem)
{
	t_3dPoint	p;
	char		**coord;

	coord = ft_split(elem, ',');
	p.x = str_to_fixed(coord[0]);
	p.y = str_to_fixed(coord[1]);
	p.z = str_to_fixed(coord[2]);
	free_split(coord);
	return (p);
}

double	atod(char *str)
{
	double	ret;
	int		negative;
	int		i;
	int		exp;

	ret = 0;
	negative = 1;
	i = 0;
	exp = 1;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			negative = -1;
	while (char_isdigit(str[i]))
		ret = ret * 10 + (str[i++] - '0');
	if (str[i] == '.' && str[++i] != '-')
		while (char_isdigit(str[i]))
			ret += (str[i++] - '0') / pow(10, exp++);
	if (ret > 0)
		return (ret * negative);
	return (ret);
}
	// return ((ret > 0) ? (ret * negative) : (ret));
