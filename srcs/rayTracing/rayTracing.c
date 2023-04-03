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

void ray_to_screen()
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
			mlx_put_pixel(img, x, y, ray_tracing(ray, vars));
			free(ray);
		}
	}
	clock_t end_time = clock();												// illegal
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);						//
}

t_Ray_hit ray_trace(const t_Ray *ray)
{
	t_Ray_hit ray_hit;
	double distance = INFINITY;

	ray_hit.color = 0;
	ray_hit.distance = INFINITY;
	ray_hit.shape = NULL;
	ray_hit.coord = malloc(sizeof(t_Vector3d));

	ray_checkhit(ray, &ray_hit, &distance);
	if (ray_hit.color && distance < ray_hit.distance)
	{
		ray_hit.distance = distance;
		*ray_hit.coord = Vector3d_add(ray->origin, Vector3d_mult(ray->direction, distance));
	}
	return ray_hit;
}

int32_t light(int32_t color, const t_Ray *ray, t_Ray_hit hit){
	t_Vector3d cc = ray->origin;
	t_Vector3d cd = ray->direction;
	t_Vector3d sc = Point3d_to_Vector3d(hit.shape->coord);
	
	double sr = to_double(hit.shape->diameter)/2;
	double t = Vector3d_dot(Vector3d_sub(sc, cc), cd)/ Vector3d_dot(cd, cd) ;
	double c = 0.0;
	t_Vector3d p = Vector3d_add(cc, Vector3d_mult(cd, t));
	double y = Vector3d_length(Vector3d_sub(sc,p));
	if(y < sr)
	{
		double x = sqrt((sr * sr) - (y * y));
		double t1 = t + x;
		c = remap( sc.y - sr, sc.y, t1);
		color = brightness(color, c);
	}
	return color;
}



int32_t ambient(int32_t color){
	// uint32_t ac = init_vars()->ambient_light->color;
	// t_rgba rgba_ac = separate_color_rgba(ac);
	t_rgba rgba = separate_color_rgba(color);
	// double	intensity = to_double(init_vars()->ambient_light->light_ratio);
	color = brightness(color, to_double(init_vars()->ambient_light->light_ratio));
	// color = mix_colors(color, ac, 1);




	return ((rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | 255);
}
int32_t ray_tracing(const t_Ray *ray, t_Vars *vars) //returns a color
{
	int32_t color;    
	t_Ray_hit hit = ray_trace(ray);
	if (!hit.color) 
		return BLACK;
	else
		color = hit.color;
//add light
	// color = light(color, ray, hit);

//add reflection

//add antialiasing

//add ambiantlight
	color = ambient(color);
	// free(hit.coord);
		(void) vars;
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