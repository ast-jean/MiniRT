#include "../../include/miniRT.h"
#include <math.h>
#include <time.h> //remove before sending project

// bool solveQuadratic(double a,double b, double c, double x0, double x1)//UNUSED
// {
//     double discr = b * b - 4 * a * c;
//     if (discr < 0) return false;
//     else if (discr == 0) x0 = x1 = - 0.5 * b / a;
//     else {
//         double q = (b > 0) ?
//             -0.5 * (b + sqrt(discr)) :
//             -0.5 * (b - sqrt(discr));
//         x0 = q / a;
//         x1 = c / q;
//     }
//     if (x0 > x1){
// 		double tmp = x1;
// 		x1 = x0;
// 		x0 = tmp;
// 	}
//     return true;
// }

void 	ray_to_screen()
{
	t_Vars *vars = init_vars();
	mlx_image_t *img = vars->img;
	uint32_t	x;
	uint32_t	y = -1;
	/**/clock_t start_time = clock(); // illegal

	while (++y < HEIGHT) 
	{
		x = -1;
		while (++x < WIDTH) 
		{
			t_Ray ray = ray_init_to_screen(vars, x, y);
			mlx_put_pixel(img, x, y, ray_tracing(ray));
			// free(ray);
		}
	}
	/**/clock_t end_time = clock();												// illegal
	/**/double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	/**/printf("Render time: %f seconds\n", elapsed_time);						//
}

// t_Vector3d shape_normal(const t_shape *shape, const t_Vector3d point)
// {
//     t_shape *sphere = (t_shape *)shape;
//     t_Vector3d normal = Vector3d_sub(point, sphere->coord);
//     normal = Vector3d_unit(normal);
//     return normal;
// }

// void put_line(t_Vector3d p1, t_Vector3d p2, t_Vars *vars, int color)
// {
//     double x1 = p1.x;
//     double y1 = p1.y;
//     double x2 = p2.x;
//     double y2 = p2.y;

//     double dx = fabs(x2 - x1);
//     double dy = fabs(y2 - y1);
//     double sx = x1 < x2 ? 1 : -1;
//     double sy = y1 < y2 ? 1 : -1;
//     double err = dx - dy;

//     while (1)
//     {
//         mlx_put_pixel(vars->img, x1, y1, color);
//         if (x1 == x2 && y1 == y2)
//             break;
//         double e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x1 += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }

t_Ray_hit ray_trace(const t_Ray ray, float dist)
{
	t_Ray_hit ray_hit;
	float distance = dist;

	// ray_hit.color = 0;
	ray_hit.distance = dist;
	// ray_hit.shape = NULL;
	ray_hit.coord = malloc(sizeof(t_Vector3d));

	ray_checkhit(ray, &ray_hit, &distance);
	if (ray_hit.color && distance < ray_hit.distance)
	{
		ray_hit.distance = distance;
		*ray_hit.coord = Vector3d_add(ray.o, Vector3d_mult(ray.d, distance));
	}
	return ray_hit;
}

int32_t shading_sp(int32_t color, const t_Ray *ray, t_Ray_hit hit){
	t_Vector3d cc = ray->o;
	t_Vector3d cd = ray->d;
	t_Vector3d sc = hit.shape->coord;
	
	float sr = hit.shape->radius;
	float t = Vector3d_dot(Vector3d_sub(sc, cc), cd)/ Vector3d_dot(cd, cd) ;
	float c = 0.0f;
	t_Vector3d p = Vector3d_add(cc, Vector3d_mult(cd, t));
	float y = Vector3d_length(Vector3d_sub(sc,p));
	if(y < sr)
	{
		float x = sqrtf((sr * sr) - (y * y));
		float t1 = t + x;
		c = remap( sc.y - sr, sc.y, t1);
		color = brightness(color, c);
	}
	return color;
}



uint32_t	ambient(uint32_t color){
	uint32_t	ac;
	ac = init_vars()->ambient_light->color;
	color = brightness(color, (float)init_vars()->ambient_light->light_ratio/100);
	color = mix_colors(color, ac, (float)init_vars()->ambient_light->light_ratio/100);
	return (color);
}

int32_t ray_tracing(const t_Ray ray) //returns a color
{
	int32_t color;    
	t_Ray_hit hit = ray_trace(ray, INFINITY);
	if (!hit.color) 
		return BLACK;
	else
		color = hit.color;
	// color = light(color, ray, hit);
//add light
	if (!light_is_visible(init_vars(), &hit))
		color = brightness(color, 0.2);
	// printf("light_is_visible = %d\n",light_is_visible(init_vars(), &hit));

//add shading depending on object



//add reflection

//add antialiasing //optional


//add ambiantlight
	color = ambient(color);

	// free(hit.coord);
		// (void) vars;
	return (color);
}

// }
/*

		   ____
		,dP9CGG88@b,
	  ,IPIYYICCG888@@b,
	 dIiIIIIIICGG8888@b
	dCIIIIIIICCGG8888@@b
____GCCIIIICCCGGG8888@@@__________________
	GGCCCCCCCGGG88888@@@
	GGGGCCCGGGG88888@@@@...
	Y8GGGGGG8888888@@@@P.....
	 Y88888888888@@@@@P......
	 `Y8888888@@@@@@@P'......
		`@@@@@@@@@P'.......
		   """"........
*/