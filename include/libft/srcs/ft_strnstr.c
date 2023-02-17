/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:39:15 by ast-jean          #+#    #+#             */
/*   Updated: 2022/07/18 11:17:04 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *n, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;
	char	*h;

	i = 0;
	h = (char *)haystack;
	n_len = ft_strlen((char *)n);
	if (haystack == n || n_len == 0)
		return (h);
	while (h[i] && i < len)
	{
		j = 0;
		while (i + j < len && h[i + j] != '\0' && h[i + j] == n[j])
		{
			j++;
			if (j == n_len)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
