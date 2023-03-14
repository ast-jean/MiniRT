/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:25:43 by slavoie           #+#    #+#             */
/*   Updated: 2023/03/13 16:43:55 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
	Initialise le fixed_point à la valeur du "double" passées en paramètre et
	le scale 

	slavoie
*/
// void	init_fp(t_Fixed *fp, double start_value) // TOFIX 
// {
// 	fp->value = start_value * fixed_scale;
// }

void	set_value(t_Fixed *fp, double value)
{
		fp->value = value * fixed_scale;
}

int	to_int(t_Fixed fp)
{
	return (fp.value / fp.scale);
}

double	to_double(t_Fixed fp)
{
	return ((double) fp.value / fixed_scale);
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