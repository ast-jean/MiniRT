/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:25:43 by slavoie           #+#    #+#             */
/*   Updated: 2023/04/17 15:45:37 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_Vector3d Point3d_to_Vector3d(t_3dPoint point)
{
	t_Vector3d	vec;

	vec.x = to_double(point.x);
	vec.y = to_double(point.y);
	vec.z = to_double(point.z);
	return (vec);
}

t_Fixed fp_init(double value)
{
	t_Fixed fp;
	// fp.value = value;
	set_value(&fp, value);
	return (fp);
}

void	set_value(t_Fixed *fp, double value)
{
	fp->value = value * fp_scale;
}

int	to_int(t_Fixed fp)
{
	return (fp.value / fp_scale);
}

double	to_double(t_Fixed fp)
{
	return ((double) fp.value / fp_scale);
}

/*
	Cette fonction effectue l'operand sur un nombre variable d'argument 
	et renvoie le résultat en type double

	operand = le signe à utilisé pour l'opération
	
	num_args = le nombre d'argument qui seront passées à la fonction, si 
	plus d'arguments sont passées que le nombre annoncées l'opération s'effetue 
	sur une valeur non initialisé. La fonction ne planteras pas, ATTENTION !!!

	... = tous les fixed_point à utilisé dans la chaine d'opération

	slavoie
*/
double	fp_cal(char operand, int num_args, ...)
{
	va_list	args;
	int		i;
	double	result;
	t_Fixed	fp;

	va_start(args, num_args);
	fp = va_arg(args, t_Fixed);
	result = to_double(fp);
	i = 0;
	while (i < num_args - 1)
	{
		fp = va_arg(args, t_Fixed);
		if (operand == '+')
			result = result + to_double(fp);
		else if (operand == '-')
			result = result - to_double(fp);
		else if (operand == '*')
			result = result * to_double(fp);
		else if (operand == '/')
			result = result / to_double(fp);
		i++;
	}
	va_end(args);
	return (result);
}

// int	main(void)
// {
// 	t_Fixed	fp;
// 	t_Fixed	fp2;
// 	t_Fixed	fp3;
// 	t_Fixed	fp4;

// 	fp.value = 1234;
// 	fp.scale = 256;
// 	fp2.value = 7895;
// 	fp2.scale = 256;
// 	fp3.value = 5753;
// 	fp3.scale = 256;
// 	fp4.value = 7643;
// 	fp4.scale = 256;

// 	int entier = to_int(fp);
// 	double reel = to_double(fp);
// 	double zero = 0;
// 	fp_cal('+', 4, fp, fp2, fp3, fp4);
// 	fp_cal('-', 4, fp, fp2, fp3, fp4);
// 	fp_cal('*', 4, fp, fp2, fp3, fp4);
// 	fp_cal('/', 4, fp, fp2, fp3, fp4);
// 	printf("Int: %i, Double: %f, Zéro: %f\n", entier, reel, zero);
// }


double Vector3d_distance(t_Vector3d point, t_Vector3d end_point)
{
    double dx = end_point.x - point.x;
    double dy = end_point.y - point.y;
    double dz = end_point.z - point.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}


void draw_ray(t_Ray *ray, double x, double y, double distance)
{
    int i;
    int x2, y2;
    int color = 0xFFFFFF; // couleur du rayon (blanc)

    // On calcule les coordonnées du deuxième point du rayon
    x2 = x + (ray->d.x * distance);
    y2 = y + (ray->d.y * distance);

    // On vérifie que les coordonnées ne dépassent pas les limites de l'écran
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    if (x2 < 0 || x2 >= WIDTH || y2 < 0 || y2 >= HEIGHT)
        return;

    // On dessine une ligne entre les deux points en ajoutant un effet de profondeur
    for (i = 0; i < distance; i++)
    {
        double depth = remap(0.0, distance, i); // effet de profondeur
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        r = (int)(r * depth);
        g = (int)(g * depth);
        b = (int)(b * depth);
        int new_color = (r << 16) | (g << 8) | b;
        mlx_put_pixel(init_vars()->img, x + (ray->d.x * i), y + (ray->d.y * i), new_color);
    }
}


// void draw_ray(t_Ray *ray)
// {
//     int i;
//     int color = 0xFFFFFF; // couleur du rayon (blanc)
//     double distance = 2000; // distance maximale de propagation du rayon
// 	t_Vars *vars = init_vars();
//     t_Vector3d origin =  Point3d_to_Vector3d(init_vars()->camera->coord); // origine du rayon (position de la caméra)
//     t_Vector3d direction = Vector3d_unit(Vector3d_sub(Vector3d_add(ray->origin, ray->direction), origin)); // direction du rayon à partir de la caméra
//     t_Vector3d point = origin; // point actuel du rayon
    
//     // On calcule les coordonnées du deuxième point du rayon en fonction de la distance maximale
//     t_Vector3d end_point = Vector3d_add(point, Vector3d_mult(direction, distance));

//     // On dessine une ligne entre les deux points avec une couleur réduite pour l'effet de profondeur
//     int color_depth = color & 0x00FFFFFF; // couleur sans la composante alpha
//     double depth_scale = 0.7; // échelle de la réduction de la couleur en fonction de la distance
//     double dist = Vector3d_distance(point, end_point); // distance entre les deux points
//     double depth = 0; // profondeur actuelle du rayon
//     for (i = 0; i < dist; i++)
//     {
//         depth = remap(0, dist, i); // on calcule la profondeur actuelle en fonction de la distance
//         mlx_put_pixel(vars->img, point.x, point.y, brightness(color_depth, 1 - depth_scale * depth)); // on dessine le pixel avec une couleur réduite
//         point = Vector3d_add(point, direction); // on passe au point suivant du rayon
//     }
	
// }






// void draw_ray(t_Ray *ray, double x, double y, double distance)
// {
//     int i;
//     int x2, y2;
//     int color = 0xFFFFFF; // couleur du rayon (blanc)
// 	t_Vars *vars = init_vars();

//     // On calcule les coordonnées du deuxième point du rayon
//     x2 = (int)(x + (ray->direction.x * distance));
//     y2 = (int)(y + (ray->direction.y * distance));

//     // On dessine une ligne entre les deux points
//     mlx_put_pixel(vars->img, (int)x, (int)y, color);
//     mlx_put_pixel(vars->img, (int)x2, (int)y2, color);
//     for (i = 1; i < distance; i++)
//     {
//         mlx_put_pixel(vars->img,  (int)(x + (ray->direction.x * i)), (int)(y + (ray->direction.y * i)), color);
//     }
// }