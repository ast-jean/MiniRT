/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:25:43 by slavoie           #+#    #+#             */
/*   Updated: 2023/03/08 15:51:12 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int toInt(t_Fixed n)
{
	return((n.entier * 100) + n.decimal);
}

double toDouble(t_Fixed n)
{
	return((double)n.entier + ((double)n.decimal) / 100);
}

int main()
{

	t_Fixed f = {123, 51}; // Crée un nombre à virgule fixe avec une partie entière de 123 et une partie décimale de 45

	int entier = toInt(f); // Convertit le nombre à virgule fixe en un entier (12345)
	double reel = toDouble(f); // Convertit le nombre à virgule fixe en un double (123.45)
	double zero = 0;

	printf("Nombre à virgule fixe : %d.%d\n", f.entier, f.decimal);
	printf("Entier : %d\n", entier);
	printf("Double : %f\n", reel);
	printf("Zéro : %f\n", zero);




	// t_Fixed f;
	// t_Fixed f2;

	// f.entier = 123;
	// f.decimal = 45;

	// f2.entier = 3;
	// f2.decimal = 14;


	// printf("F toInt = %i\n", toInt(f));
	// printf("F toDouble = %f\n", toDouble(f));

	// printf("F2 toInt = %i\n", toInt(f2));
	// printf("F2 toDouble = %f\n", toDouble(f2));
	// // printf("toInt = %i\n", toInt(n));
}