#include "../../include/miniRT.h"
#include <math.h>

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

	while (++y < (uint32_t)HEIGHT) 
	{
		x = -1;
		while (++x < (uint32_t)WIDTH) 
		{
			mlx_put_pixel(img, x, y, traceRay(x, y)); //cast_ray output a color
		}
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

// double	lenght2(double x, double y, double z)
// {
// 	return (sqr(x) + sqr(y) + sqr(z));
// }

// double	lenght(double x, double y, double z)
// {
// 	return (sqrt(lenght(x, y, z)));
// }


// bool	is_ray_in_cercle(t_shape cercle){
// 	hypot();
// 	double r = cercle.diameter / 2;
// 	t = dot();
// 	if (y < r)
// 		return (printf("not in cercle"), 0);
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


