#include "../../include/miniRT.h"
#include <math.h>
#include <time.h> //remove before sending project



void 	ray_to_screen()
{
	t_Vars *vars = init_vars();
	mlx_image_t *img = vars->img;
	uint32_t	x;
	uint32_t	y = -1;
	clock_t start_time = clock(); // illegal

	while (++y < HEIGHT) 
	{
		x = -1;
		while (++x < WIDTH) 
		{
			t_Ray ray = ray_init_to_screen(vars, x, y);
			mlx_put_pixel(img, x, y, ray_tracing(ray));
		}
	}
	printf("i = %d\n", vars->i);
	clock_t end_time = clock();												// illegal
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);						//
}

t_Vector3d shape_normal(const t_shape *shape, const t_Vector3d point)
{
    t_shape *sphere = (t_shape *)shape;
    t_Vector3d normal = Vector3d_sub(point, Point3d_to_Vector3d(sphere->coord));
    normal = Vector3d_unit(normal);
    return normal;
}


t_Ray_hit ray_trace(const t_Ray ray, double dist)
{
	t_Ray_hit ray_hit;
	double distance = dist;

	ray_hit.distance = dist;
	ray_checkhit(ray, &ray_hit, &distance);
	ray_hit.distance = distance;

	return (ray_hit);
}

uint32_t ambient(uint32_t color){
	uint32_t ac = init_vars()->ambient_light->color;
	color = brightness(color, to_double(init_vars()->ambient_light->light_ratio));
	color = mix_colors(color, ac, to_double(init_vars()->ambient_light->light_ratio));
	return (color);
}

uint32_t ray_tracing(const t_Ray ray) //returns a color
{
	uint32_t color;
	t_Ray_hit hit = ray_trace(ray, INFINITY);
	if (!hit.color) 
		return BLACK;
	else
		color = hit.color;
//add light
	// if (light_is_visible(init_vars(), &hit))
	// 	color = brightness(color, 0.5);

//add reflection

//add ambiantlight
	// color = ambient(color);
	return (color);
}
