/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:56:37 by ast-jean          #+#    #+#             */
/*   Updated: 2023/05/17 13:55:23 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_rgba	specular(t_rgba obj_color, double coefficient, double shine)
{
	t_rgba	specular;
	t_rgba	highlight;

	highlight = rgba_init(255, 255, 255);
	highlight = brightness(highlight, shine);
	specular = rgba_add(brightness(obj_color, shine), highlight);
	return (brightness(specular, coefficient));
}

t_rgba	mix_colors_light(t_Ray_hit hit, t_shape shape, double coeff)
{
	double	specular_coeff;
	t_rgba	result;
	double	l_r;
	double	a_r;

	specular_coeff = coeff;
	result = separate_color_rgba(shape.color);
	l_r = to_double(init_vars()->light->light_ratio);
	a_r = to_double(init_vars()->ambient_light->light_ratio);
	if (hit.hit)
		coeff = a_r;
	else
	{
		// printf("Bef=r.%d, g.%d, b.%d \n", result.r, result.g, result.b);
		
		result = mix_colors(result, remove_excess(separate_color_rgba(init_vars()->light->color)), l_r);
		coeff = coeff * l_r + a_r;
	
		// printf("After=r.%d, g.%d, b.%d \n", result.r, result.g, result.b);
	}
	result = mix_colors(result, (separate_color_rgba(init_vars()->ambient_light->color)), a_r);
	result = brightness(result, coeff);

	if (specular_coeff > 0 && !hit.hit)
		result = rgba_add(result, \
		specular(result, pow(specular_coeff, 100), l_r));
	return (result);
}

t_rgba	brightness(t_rgba color, double mix_factor)
{
	t_rgba	result;

	mix_factor = fmax(0.0, fmin(1.0, mix_factor));
	result.r = (uint8_t)(color.r * mix_factor);
	result.g = (uint8_t)(color.g * mix_factor);
	result.b = (uint8_t)(color.b * mix_factor);
	result.a = 255;
	return (result);
}

t_rgba	mix_colors(t_rgba color1, t_rgba color2, double mix_factor)
{
	t_rgba	result;

	static int g = 0;

color2.r=(255 - color2.r);
color2.g=(255 - color2.g);
color2.b=(255 - color2.b);

color2 = remove_excess(color2);
	mix_factor = fmax(0.0, fmin(1.0f, mix_factor));
	result.r = (uint8_t)((color1.r) + ((color2.r)  * mix_factor));
	result.g = (uint8_t)((color1.g) + ((color2.g)  * mix_factor));
	result.b = (uint8_t)((color1.b) + ((color2.b)  * mix_factor));
	result.a = 255;
	return (result);
}
