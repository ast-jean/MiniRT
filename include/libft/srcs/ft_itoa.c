/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:38:36 by ast-jean          #+#    #+#             */
/*   Updated: 2022/07/18 11:15:31 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_char(int n)
{
	long	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char	*c;
	int		i;
	long	n;

	n = nb;
	c = malloc(sizeof(char) * (count_char(n) + 1));
	if (!c)
		return (NULL);
	i = count_char(n);
	c[i--] = '\0';
	if (n < 0)
		n *= -1;
	while (i >= 0)
	{
		c[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	if (nb < 0)
		c[0] = '-';
	return (c);
}
