#include "../../include/miniRT.h"
#include <math.h>
#include <time.h> //remove before sending project

bool solveQuadratic(double a,double b, double c, double x0, double x1)//UNUSED
{
    double discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) x0 = x1 = - 0.5 * b / a;
    else {
        double q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1){
		double tmp = x1;
		x1 = x0;
		x0 = tmp;
	}
    return true;
}

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
			t_Ray *ray = ray_init_to_screen(vars, x, y);
			mlx_put_pixel(img, x, y, ray_tracing(*ray));
			free(ray);
		}
	}
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

void put_line(t_Vector3d p1, t_Vector3d p2, t_Vars *vars, int color)
{
    double x1 = p1.x;
    double y1 = p1.y;
    double x2 = p2.x;
    double y2 = p2.y;

    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);
    double sx = x1 < x2 ? 1 : -1;
    double sy = y1 < y2 ? 1 : -1;
    double err = dx - dy;

    while (1)
    {
        mlx_put_pixel(vars->img, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        double e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}



// t_Ray_hit ray_trace(const t_Ray *ray)
// {
//     t_Ray_hit ray_hit;
//     // double distance = INFINITY;
//     double distance = 10000;

//     ray_hit.color = 0;
//     // double distance = INFINITY;
//     ray_hit.distance = 10000;
//     ray_hit.shape = NULL;
//     ray_hit.coord = malloc(sizeof(t_Vector3d));

//     ray_checkhit(ray, &ray_hit, &distance);

//     if (ray_hit.color && distance < ray_hit.distance)
//     {
//         ray_hit.distance = distance;
//         *ray_hit.coord = Vector3d_add(ray->origin, Vector3d_mult(ray->direction, distance));
//         t_Vector3d normal = shape_normal(ray_hit.shape, *ray_hit.coord);
//         t_Vector3d normal_end = Vector3d_add(*ray_hit.coord, Vector3d_mult(normal, 50.0));
//         put_line(*ray_hit.coord, normal_end, init_vars(), 0xFF0000); // Dessine la normale
//     }

//     return ray_hit;
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

uint32_t ambient(uint32_t color){
	uint32_t ac = init_vars()->ambient_light->color;
	color = brightness(color, to_double(init_vars()->ambient_light->light_ratio));
	color = mix_colors(color, ac, to_double(init_vars()->ambient_light->light_ratio));
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
//add light
	// color = light(color, ray, hit);

//add reflection

//add antialiasing //optional

//add ambiantlight
	light_is_visible(init_vars(), &hit);
	// printf("light_is_visible = %d\n",light_is_visible(init_vars(), &hit));

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