/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:49:04 by mtrembla          #+#    #+#             */
/*   Updated: 2023/02/10 12:50:12 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_gnljoin(char *s, char c)
{
	char	*out;
	int		n;

	n = 2;
	if (s)
		while (*s && s++)
			n++;
	out = malloc(n * sizeof(char));
	out[--n] = '\0';
	out[--n] = c;
	if (s)
	{
		while (n--)
			out[n] = *--s;
		free(s);
	}
	return (out);
}

//gnl with auto free
char	*ft_gnl(int fd)
{
	char		c;
	static char	*line = NULL;

	if (line)
		free(line);
	line = NULL;
	while (read(fd, &c, 1) && (c != '\n' || line == NULL))
	{
		if (c == '\n')
			continue ;
		line = ft_gnljoin(line, c);
	}
	return (line);
}
