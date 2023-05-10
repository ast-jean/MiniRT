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
	clock_t end_time = clock();												// illegal
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);						//
}

t_Ray_hit init_Ray_hit()
{
	t_Ray_hit rh;
	rh.color = 0;
	rh.coord = Vector3d_init(0,0,0);
	rh.distance = 0;
	rh.normal = Vector3d_init(0,0,0);
	rh.shape = NULL;
	rh.hit = false;
	return (rh);
}

/// @brief Initialize the information of the intersected point
/// @param ray		:The ray it initialized from
/// @param dist_bef	:The distance from the hit coordinate to the other intersection, 
///					 if non INFINITY it is the distance to the light.
///					 if the distance < dist_bef it means an object was caught inbetween
/// @param shape 	:The object the ray originated from. If non Null it -> Light or reflection
/// @return 		:The Ray_hit struct 
t_Ray_hit ray_trace(const t_Ray ray, double dist_bef, t_shape *shape)
{
	t_Ray_hit light_ray_hit = init_Ray_hit();
	double distance = dist_bef;

	if (!shape)
		ray_checkhit(ray, &light_ray_hit, &distance, NULL);
	else
		ray_checkhit(ray, &light_ray_hit, &distance, shape);
	return (light_ray_hit);
}


uint32_t ray_tracing(const t_Ray ray) //returns a color
{
	uint32_t color;
	t_Ray_hit hit = ray_trace(ray, INFINITY, NULL); //first draw shape
	if (!hit.color) 
		return BLACK;
	else
		color = hit.color;
//add shading
	color = rgba_to_int32_t(shading(&hit, separate_color_rgba(color)));
//add reflection
	//color = mixcolor (color, other object, reflection_intensity)
	return (color);
}
