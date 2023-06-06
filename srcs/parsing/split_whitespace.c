/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:28:22 by mtrembla          #+#    #+#             */
/*   Updated: 2023/06/06 11:55:50 by ast-jean         ###   ########.fr       */
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

	word_count = 0;
	in_word = 0;
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
	int	start;
	int	i;
	int	j;

	start = 0;
	i = 0;
	j = 0;
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

	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * ((nbr_of_strs(str)) + 1));
	if (!tab)
		return (NULL);
	tab = create_tab(tab, str);
	return (tab);
}
