/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:55:18 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/15 15:56:14 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int32_t	rgba_to_int32_t(t_rgba rgba)
{
	return ((rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | rgba.a);
}

t_rgba	rgba_init(int r, int g, int b)
{
	t_rgba	rgba;

	rgba.r = (int8_t)r;
	rgba.g = (int8_t)g;
	rgba.b = (int8_t)b;
	rgba.a = (int8_t)255;
	return (rgba);
}

t_rgba	separate_color_rgba(uint32_t color)
{
	t_rgba	rgba;

	rgba.r = (color >> 24) & 0xFF;
	rgba.g = (color >> 16) & 0xFF;
	rgba.b = (color >> 8) & 0xFF;
	rgba.a = color & 0xFF;
	return (rgba);
}

t_rgba	rgba_add(t_rgba a, t_rgba b)
{
	t_rgba	result;

	result.r = fmin(a.r + b.r, 255);
	result.g = fmin(a.g + b.g, 255);
	result.b = fmin(a.b + b.b, 255);
	return (result);
}

t_rgba	remove_excess(t_rgba c)
{
	int	min;

	min = c.r;
	if (c.g < min)
		min = c.g;
	if (c.b < min)
		min = c.b;
	c.r -= min;
	c.g -= min;
	c.b -= min;
	return (c);
}
