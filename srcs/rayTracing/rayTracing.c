#include "../../include/miniRT.h"
#include <math.h>



bool solveQuadratic(double a,double b, double c, double x0, double x1)
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

// BASE

void ray_to_screen()
{
	t_Vars *vars = init_vars();
	mlx_image_t *img = vars->img;
	uint32_t	x;
	uint32_t	y = -1;
	int			i;

	i = 0;

		ft_putstr_fd("?Unos or dos?\n",1 );
	while (++y < HEIGHT) 
	{
		// ft_putstr_fd(ft_itoa(y), 1);
		// ft_putstr_fd("\n",1 );
		x = -1;
		while (++x < WIDTH) 
		{
			// ft_putstr_fd(" x =",1 );
		// ft_putstr_fd(ft_itoa(x), 1);

			t_Ray *ray = ray_init_to_screen(vars, x, y);
			mlx_put_pixel(img, x, y, ray_tracing(ray, vars));
			free(ray);
			
			// ft_putstr_fd("\n",1 );
			// mlx_put_pixel(img, x, y, BLUE);
		}
			// ft_putstr_fd("\n",1 );

	}





// 	t_Vars *vars = init_vars();
// 	mlx_image_t *img = vars->img;
// 	static uint32_t	x;
// 	static uint32_t	y = 0;
// 	static uint32_t	color;
	
// 		if(!color)
// 			color = RED;
// 		if (x == WIDTH)
// 			y++;
// 		x = -1;
// 		while (++x < (uint32_t)WIDTH) 
// 		{																		//		 R  G  B  N
// 			mlx_put_pixel(img, x, y, color += x^2 + 69); //damier 
// 			// mlx_put_pixel(img, x, y, ((x^2+y^2)/4)*WIDTH * 8); //damier 
// 			// mlx_put_pixel(img, x, y, ((x^2+y^2)/4)*WIDTH); //yes blue nor recusif
// 			// mlx_put_pixel(img, x, y, ((x^2 + y^2) * 0x009900FF) % 0x00FF00FF); //yes blue nor recusif
// 			// mlx_put_pixel(img, x, y, (x^10 + y^10) * 0x000000FF); //yes blue nor recusif
// 			// mlx_put_pixel(img, x, y, ((x+y)/4)*HEIGHT); //yes blue nor recusif

// 		}
// 		if (y == HEIGHT)
// 			y = 0;
}

t_Ray_hit ray_trace(const t_Ray *ray)
{
	t_Ray_hit ray_hit;
	double distance = 1.0 / 0.0f;
	int32_t color = 0;

	//initializer
	ray_hit.color = 0;
	ray_hit.distance = 0;
	ray_hit.shape = NULL;
	ray_hit.coord = malloc(sizeof(t_Vector3d));

	ray_checkhit(ray, &ray_hit, &distance);
	if(distance < INFINITY)
	// printf("color = %d|rhd = %f|distance = %f\n", ray_hit.color, ray_hit.distance, distance);
	if (ray_hit.color && distance < ray_hit.distance)
	{
		ray_hit.distance = distance;
		ray_hit.color = color;
		*ray_hit.coord = Vector3d_add(ray->origin, Vector3d_mult(ray->direction, distance));
	}
	return ray_hit;
}

int32_t saturate(int32_t color, double scale){
  uint8_t r = (color >> 24) & 0xFF;
  uint8_t g = (color >> 16) & 0xFF;
  uint8_t b = (color >> 8) & 0xFF;
  uint8_t a = color & 0xFF;

  r *= scale;
  g *= scale;
  b *= scale;

  return ((r << 24) | (g << 16) | (b << 8) | a);
}

double remap(double a, double b, double t)
{
	return ((t-a)/(b-a));
}

int32_t ray_tracing(const t_Ray *ray, t_Vars *vars) //returns a color
{
	int32_t color;    
	t_Ray_hit hit = ray_trace(ray);
	if (hit.color == 0) 
		return BLACK;
	else
		color = hit.color;

	(void) vars;
//add ambiantlight
	// t_Vector3d cc = Point3d_to_Vector3d(vars->camera->coord);
	// t_Vector3d cd = Point3d_to_Vector3d(vars->camera->orientation);
	// t_Vector3d sc = Point3d_to_Vector3d(hit.shape->coord);
	
	// double sr = to_double(hit.shape->diameter)/2;
	// double t = Vector3d_dot(Vector3d_sub(sc, cc), cd);


	// t_Vector3d p = Vector3d_add(cc, Vector3d_mult(cd, t));
	// t_Vector3d yy = Vector3d_sub(sc,p);
	// double y = Vector3d_length(yy);
	
	// if(y<sr){
	// 	double x = sqrt((sr * sr) - (y * y));
	// 	double t1 = t + x;
	// 	double c = remap(sc.z, sc.z - sr, t1);
	// // printf("c =%f|t1=%f|sc.z=%f|sr=%f|x=%f|y=%f|t=%f|\n", c, t1, sc.z, sr, x,y, t);
	// // printf("px=%f|py=%f|pz=%f|\n", p.x,p.y,p.z);
	// // printf("ccx=%f|ccy=%f|ccz=%f|\n", cc.x,cc.y,cc.z);
	// // printf("scx=%f|scy=%f|scz=%f|\n", sc.x,sc.y,sc.z);
	// // printf("yyx=%f|yyy=%f|yyz=%f|\n", yy.x,yy.y,yy.z);
	// color = saturate(color, c);

	// }
//add light

//add reflection
//add antialiasing
	// free(hit.coord);
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