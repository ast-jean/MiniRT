/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:39:39 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/05 17:14:53 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	nbr_of_strs(char const *str)
{
	int	word_count;
	int	in_word;

	in_word = 0;
	word_count = 0;
	while (*str)
	{
		if (!ft_isspace(*str) && !in_word)
		{
			in_word = 1;
			word_count++;
		}
		else if (ft_isspace(*str))
			in_word = 0;
		str++;
	}
	return (word_count);
}

char	**create_tab(char **tab, const char *str)
{
	int		i;
	int		start;
	int		j;

	start = 0;
	j = 0;
	i = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
		{
			start = i;
			while (str[i] && !ft_isspace(str[i]))
				i++;
			tab[j] = malloc(sizeof(char) * (i - start + 1));
			ft_strlcpy(tab[j++], &str[start], (i - start + 1));
		}
		if (str[i])
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**split_on_space(char const *str)
{
	char	**tab;
	int		strs;

	if (!str)
		return (NULL);
	strs = nbr_of_strs(str);
	tab = malloc(sizeof(char *) * (strs + 1));
	if (!tab)
		return (NULL);
	tab = create_tab(tab, str);
	return (tab);
}
