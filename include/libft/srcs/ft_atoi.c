/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:54:55 by ast-jean          #+#    #+#             */
/*   Updated: 2022/07/18 11:14:52 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\t')
		return (1);
	if (c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	long	num;
	long	n;
	long	i;

	n = 1;
	i = 0;
	num = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	if (s[i] == '-')
		n *= -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		num = num * 10 + (s[i] - 48);
		i++;
	}
	return (num * n);
}
