/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:25:43 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/10 14:46:56 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_Vector3d	Point3d_to_Vector3d(t_3dPoint point)
{
	t_Vector3d	vec;

	vec.x = to_double(point.x);
	vec.y = to_double(point.y);
	vec.z = to_double(point.z);
	return (vec);
}

t_3dPoint	Vec3D_to_point3D(t_Vector3d vec)
{
	t_3dPoint	point;

	point.x = fp_init(vec.x);
	point.x = fp_init(vec.y);
	point.x = fp_init(vec.z);
	return (point);
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
