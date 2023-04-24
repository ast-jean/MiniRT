#include "../../include/miniRT.h"
#include <math.h>

double		spec_coeff(t_Ray_hit hit,  t_Ray ray)
{
	t_Vector3d		light_ray;
	t_Vector3d		reflection;
	t_Vector3d		back_view_ray;
	double			result;


	t_Vector3d light_coord = Point3d_to_Vector3d(init_vars()->light->coord);

	light_ray = Vector3d_norm(Vector3d_sub(light_coord, hit.coord));
	reflection = Vector3d_add(light_ray, \
				Vector3d_mult(Vector3d_mult(hit.normal, \
				Vector3d_dot(light_ray, hit.normal)), -2));
	back_view_ray = Vector3d_norm(Vector3d_sub(hit.coord, ray.o));
	result = fmax(Vector3d_dot(reflection, back_view_ray), 0);
	result = pow(result, 10);
	return (result);
}

int32_t rgba_to_int32_t(t_rgba rgba)
{
	return ((rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | rgba.a);
}


t_rgba	specular(t_Ray_hit hit,  t_Ray ray)
{
	t_rgba	specular;
	t_rgba	highlight;
	double		shine;
	double		coeff;

	shine = 0.1;
	highlight.r = 255;
	highlight.g = 255;
	highlight.b = 255;
	highlight = brightness(highlight, (255 - shine));
	specular = rgba_add(brightness(separate_color_rgba(hit.color), shine), highlight);
	coeff = spec_coeff(hit, ray);
	return (brightness(specular, coeff));
}

t_rgba rgba_init()
{
	t_rgba rgba;
	rgba.r = 0;
	rgba.g = 0;
	rgba.b = 0;
	rgba.a = 0;
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

t_rgba	mix_colors_light(t_Ray_hit hit,  t_Ray ray, t_shape shape, double coeff)
{

	t_rgba	result = rgba_init();
	// t_rgba	light_color = rgba_init();
	double	l_r = to_double(init_vars()->light->light_ratio);
	t_rgba	object_color = rgba_init();
	t_rgba	light_color = separate_color_rgba(init_vars()->light->color); //was lcolor
//add ambient somewhere here

	// light_color = brightness(lcolor, l_r);
	object_color = separate_color_rgba(shape.color);
	t_rgba res1 = mix_colors(light_color, object_color, l_r);
	// result = brightness(res1, coeff);
	result = rgba_add(brightness(res1, coeff), specular(hit, ray)); //phong specular
	(void)ray;
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


double remap(double a, double b, double t)
{
	return ((t-a)/(b-a));
}

// t_rgba ambient(uint32_t color)
// {
// 	t_rgba ac;
// 	 = init_vars()->ambient_light->color;
// 	color = brightness(color, to_double(init_vars()->ambient_light->light_ratio));
// 	color = mix_colors(color, ac, to_double(init_vars()->ambient_light->light_ratio));
// 	return (color);
// }
