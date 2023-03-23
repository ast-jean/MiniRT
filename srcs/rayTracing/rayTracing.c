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


/// @brief Projete un ray dans le plan 3D virtuel et compare les coordonnées des objects
/// @param x coordonée x de l'img
/// @param y coordonée x de l'img
/// @param Sx coordonée x relative à l'écran projeter 
/// @param Sy coordonée y relative à l'écran projeter 
/// @return returne la couleur de l'objet trouvé sinon NULL
uint32_t traceRay(uint32_t x, uint32_t y)
{
	t_Vars *vars = init_vars();
	double imageAspectRatio = (double)WIDTH / (double)HEIGHT; // assuming width > height

	
	double Sx = (2 * ((x + 0.5) / (double)WIDTH ) - 1) * tan(vars->camera->FOV / 2 * M_PI / 180) * imageAspectRatio;
	double Sy = (1 - 2 * ((y + 0.5) / (double)HEIGHT) * tan(vars->camera->FOV / 2 * M_PI / 180));
	(void)Sx, (void)Sy;
	//normalize with direction;

	//cycle through objs
	//hit_objects() //return object color;

	return (RED);
}

// void put_circle(s_shape shape)
// {
	



// }

// t_Fixed PCR(int bx, int by, int ex, int ey)
// {
// 	while (bx < ex && by < ey)
// 	{

// 	}



// }

/// @brief Attribut la couleur retourné par traceray au pu
// void ray_to_screen(int size_x, int size_y)
// {
// 	t_Vars *vars = init_vars();
// 	mlx_image_t *img = vars->img;
// 	uint32_t	x;
// 	uint32_t	y = -1;
// 	int			i;
// 	// uint32_t	color;

// 	i = 0;
// 	while (++y < (uint32_t)HEIGHT && size_y) 
// 	{
// 		x = -1;
// 		while (++x < (uint32_t)WIDTH && size_x) 
// 		{
// 			mlx_put_pixel(img, x, y, traceRay(x, y)); //cast_ray output a color
// 			size_x--;
// 		}
// 		size_y--;
// 	}


// BASE

void ray_to_screen()
{
	t_Vars *vars = init_vars();
	mlx_image_t *img = vars->img;
	uint32_t	x;
	uint32_t	y = -1;
	int			i;

	i = 0;

	while (++y < HEIGHT) 
	{
		// ft_putstr_fd(" y =",1 );
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

	ray_checkhit(ray, &ray_hit);
	if (ray_hit.color && distance < ray_hit.distance)
	{
		ray_hit.distance = distance;
		ray_hit.color = color;
	}
	return ray_hit;
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
//add light
//add reflection
//add antialiasing

	return (color);
}
//     resultColor = closestHit.surface->material.color;
//     Vector3 collisionPoint = vec3_add(vec3_mult(ray->direction, closestHit.distance), ray->origin);
//     Material material = closestHit.surface->material;
//     if (material.reflectivity > 0.0 && depth > 0) {
//         Ray reflectedRay = ray_reflect(ray, closestHit.surface, collisionPoint);
//         if (material.reflectionNoise > 0) {
//             reflectedRay = ray_addNoise(&reflectedRay, material.reflectionNoise);
//         }
//         Color reflectionColor = ray_traceRecursive(&reflectedRay, scene, depth - 1);
//         resultColor = color_blend(reflectionColor, material.reflectivity, resultColor);
//     }
//     ShadingResult shadingResult = ray_shadeAtPoint(ray, scene, closestHit.surface, collisionPoint);    
//     resultColor = getHighlightedColor(resultColor, shadingResult, scene->ambientCoefficient);
//     resultColor = color_mult(resultColor, (MAX_VISIBLE_DISTANCE - closestHit.distance) / MAX_VISIBLE_DISTANCE);
//     return resultColor;
// }


/*


		 , - ~ ~ ~ - ,
	 , '               ' ,           x^2+y^2 = R^2
   ,                       ,         x = sqrt(R^2 - y^2)
  ,                         ,        y = len(s- p)
 ,            S              ,		 t1 = t - x
 ,            o              ,		 t2 = t + x
 ,            |  y           ,
  ,t1   x     ++            t2,
o--o----------++-----------o
p    ,                  , '
	   ' - , _ _ _ ,  '


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