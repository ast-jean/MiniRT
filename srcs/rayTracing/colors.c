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

t_rgba	mix_colors_light(t_Ray_hit hit,  t_Ray ray)
{
	t_rgba	result;
	t_rgba	light_color;
	t_rgba	object_color;
	t_rgba	lcolor = separate_color_rgba(init_vars()->light->color);

	light_color = brightness(lcolor, to_double(init_vars()->light->light_ratio));
	object_color = separate_color_rgba(hit.shape->color);
	result = brightness(mix_colors(light_color, object_color), hit.coeff);
	if (hit.coeff)
		result = rgba_add(result, specular(hit, ray)); //phong specular
	(void)ray;
	return (result);
}

t_rgba	brightness(t_rgba a, double coeff)
{
	t_rgba result;

	result.r = (int)fmin(a.r * coeff, 255);
	result.g = (int)fmin(a.g * coeff, 255);
	result.b = (int)fmin(a.b * coeff, 255);
	return (result);
}

t_rgba mix_colors(t_rgba A, t_rgba B)
{
	t_rgba	N;

	N.r = (int)fmin((A.r * B.r), 255);
	N.g = (int)fmin((A.g * B.g), 255);
	N.b = (int)fmin((A.b * B.b), 255);

    return (N);
}


double remap(double a, double b, double t)
{
	return ((t-a)/(b-a));
}

// uint32_t ambient(uint32_t color)
// {
// 	uint32_t ac = init_vars()->ambient_light->color;
// 	color = brightness(color, to_double(init_vars()->ambient_light->light_ratio));
// 	color = mix_colors(color, ac, to_double(init_vars()->ambient_light->light_ratio));
// 	return (color);
// }
