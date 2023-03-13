#include "../../include/miniRT.h"

// double	distance_between_pts(t_3dPoint center, t_3dPoint point)
// {
// 	double	x1;
// 	double	y1;
// 	double	z1;

// 	x1 = pow((toDouble(point.x) - toDouble(center.x)), 2);
// 	y1 = pow((toDouble(point.y) - toDouble(center.y)), 2);
// 	z1 = pow((toDouble(point.z) - toDouble(center.z)), 2);
// 	return (x1 + y1 + z1);
// }

// int	if_in_sphere(t_shape shape, t_3dPoint point)
// {
// 	double	r;
// 	int	ans;

// 	r = toDouble(shape.diameter) / 2;
// 	ans = distance_between_pts(shape.center, point);
// 	if (ans < (r * r))
// 		return (1);
// 	else if (ans == (r * r))
// 		return (1);
// 	else
// 		return (0);
// }

// void	insert_cercle(t_Vars vars, t_shape cercle)
// {
// 	double	r;
// 	t_3dPoint point;
	
// 	int32_t color;
// 	color = cercle.color;

// 	r = toDouble(cercle.diameter) / 2;
// 	save(point.z, toDouble(cercle.center.z) + r); 
	
// 	toDouble(cercle.center.z) + r;

// 	while (toDouble(point.z) != toDouble(cercle.center.z) && toDouble(point.z) != toDouble(cercle.center.z))
// 	{
// 		if(if_in_sphere(cercle, point))
// 			// point() is cercle color
// 	}
// }
/*
               ____
            ,dP9CGG88@b,
          ,IPIYYICCG888@@b,
         dIiIIIIIICGG8888@b
        dCIIIIIIICCGG8888@@b
________GCCIIIICCCGGG8888@@@__________________
        GGCCCCCCCGGG88888@@@
        GGGGCCCGGGG88888@@@@...
        Y8GGGGGG8888888@@@@P.....
         Y88888888888@@@@@P......
         `Y8888888@@@@@@@P'......
            `@@@@@@@@@P'.......
                """"........
*/