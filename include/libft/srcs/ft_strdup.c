/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:44:50 by ast-jean          #+#    #+#             */
/*   Updated: 2022/07/18 11:16:33 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	len;

	len = ft_strlen(s1) + 1;
	cpy = malloc(sizeof(char) * len);
	if (!cpy)
		return (0);
	cpy = ft_memcpy (cpy, s1, len);
	return (cpy);
}
