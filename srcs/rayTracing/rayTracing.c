#include "../../include/miniRT.h"
#include <math.h>

// Define a virtual camera with a position, orientation, and field of view.
void save_camera(t_dlist *l, t_Vars *vars){
	t_node *aff = l->first;

	while(aff)
	{
		t_shape *s = aff->content;
		if (ft_strcmp(s->id, "C"))
		{
			vars->camera->id = s->id;
			vars->camera->orientation = s->orientation;
			vars->camera->coord = s->coord;
			vars->camera->FOV = s->FOV;
			dlist_remove_node(l, aff);
			return ;
		}
		aff = aff->next;
	}
	printf("Not Camera found : save_camera()\n");
	return ;
}

uint32_t castRay()
{
		t_Vars *vars = init_vars();
	t_Fixed fov;
	set_value(&fov, vars->camera->FOV);
	// double imageAspectRatio = (double)WIDTH / (double)HEIGHT; // assuming width > height
	(void)vars;
	// double Px = (2 * ((to_double(x) + 0.5) / (double)WIDTH ) - 1) * tan(to_double(fov) / 2 * M_PI / 180) * imageAspectRatio;
	// double Py = (1 - 2 * ((to_double(y) + 0.5) / (double)HEIGHT) * tan(to_double(fov) / 2 * M_PI / 180));
	return (RED);
}

void ray_to_screen()
{

	

	
	t_Fixed x;
	set_value(&x, 0);
	
	t_Fixed y;
	set_value(&y, 0);

	uint32_t j = -1;
	uint32_t i = 0;
	while (++j < (uint32_t)HEIGHT) 
	{
		i = 0;
		while (i < (uint32_t)WIDTH) 
		{
			mlx_put_pixel(img, to_int(x), to_int(y), castRay()); //cast_ray output a color
			i++;
		}
	}
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


