#include "../../include/miniRT.h"
#include <math.h>

int32_t rgba_to_int32_t(t_rgba rgba)
{
	return ((rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | rgba.a);
}


t_rgba	specular(t_rgba obj_color, double coefficient)
{
	t_rgba	specular;
	t_rgba	highlight = rgba_init(255,255,255);
	double		shine;
	// double		coeff;

	shine = 0.5;
	highlight = brightness(highlight, shine);
	// specular = rgba_add(brightness(separate_color_rgba(hit.color), shine), highlight);
	specular = rgba_add(brightness(obj_color, shine), highlight);
	// coeff = spec_coeff(hit, ray);
	return (brightness(specular, coefficient));
}

t_rgba rgba_init(int r, int g, int b)
{
	t_rgba rgba;
	rgba.r = (int8_t)r;
	rgba.g = (int8_t)g;
	rgba.b = (int8_t)b;
	rgba.a = (int8_t)255;
	return (rgba);
}

t_rgba separate_color_rgba(uint32_t color)
{
	t_rgba rgba;

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

t_rgba	mix_colors_light(t_Ray_hit hit, t_Ray ray, t_shape shape, double coeff)
{
	(void)ray;
	t_rgba	result = rgba_init(0,0,0);

	double	l_r = to_double(init_vars()->light->light_ratio);
	t_rgba	object_color = rgba_init(0,0,0);
	t_rgba	light_color = separate_color_rgba(init_vars()->light->color); //was lcolor
	object_color = separate_color_rgba(shape.color);
	t_rgba res1 = mix_colors(light_color, object_color, l_r);
	if(hit.hit)
		coeff = 0;

	if(coeff > 0)
	{
		result = rgba_add(brightness(res1, coeff), specular(object_color, pow(coeff,100))); //phong specular
	}
//add ambient somewhere here
	// light_color = brightness(lcolor, l_r);
	return (result);
}

t_rgba	brightness(t_rgba color, double mix_factor)
{
	t_rgba result;
    mix_factor = fmaxf(0.0f, fminf(1.0f, mix_factor)); // Clamp mix_factor between 0 and 1

    result.r = (uint8_t)(color.r * mix_factor);
    result.g = (uint8_t)(color.g * mix_factor);
    result.b = (uint8_t)(color.b * mix_factor);
    result.a = 255;
	return (result);
}

t_rgba mix_colors(t_rgba color1, t_rgba color2, double mix_factor)
{
	t_rgba result;
    mix_factor = fmax(0.0, fmin(1.0f, mix_factor)); // Clamp mix_factor between 0 and 1

    result.r = (uint8_t)(color1.r * (1.0f - mix_factor) + color2.r * mix_factor);
    result.g = (uint8_t)(color1.g * (1.0f - mix_factor) + color2.g * mix_factor);
    result.b = (uint8_t)(color1.b * (1.0f - mix_factor) + color2.b * mix_factor);
    result.a = 255;



	// result.r = (int)fmin(((double)A.r * (double)B.r), 1);
	// result.g = (int)fmin(((double)A.g * (double)B.g), 1);
	// result.b = (int)fmin(((double)A.b * (double)B.b), 1);
	// result.a = 255;

    return (result);
}

t_rgba remove_excess(t_rgba c)
{
	if (c.r == fmin(c.r, c.b) && c.r == fmin(c.r, c.g)) 
	{
		c.r = 0;
		c.g -= c.r;
		c.b -= c.r;
	}
	else if (c.b == fmin(c.b, c.r) && c.b == fmin(c.b, c.g))
	{
		c.r -= c.b;
		c.g -= c.b;
		c.b = 0;
	}
	else if (c.g == fmin(c.g, c.r) && c.g == fmin(c.g, c.b))
	{
		c.r -= c.g;
		c.g = 0;
		c.b -= c.g;
	}
	return (c);
}

t_rgba ambient(t_rgba color)
{
	double intensity = to_double(init_vars()->ambient_light->light_ratio);
	t_rgba ac;
	ac = separate_color_rgba(init_vars()->ambient_light->color);
	// t_rgba color_add = rgba_init(0,0,0);

//if intensity == 1; color should mix 50/50
	
	// ac = remove_excess(ac);
	// color = rgba_add(remove_excess(color_add), brightness(ac, intensity));
	// color = mix_colors(color, ac, intensity);
	color = brightness(color, intensity);

	(void)intensity;
	
	return (color);
}
