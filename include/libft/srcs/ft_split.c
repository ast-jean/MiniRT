/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:09:21 by ast-jean          #+#    #+#             */
/*   Updated: 2022/07/18 11:16:28 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	boolean;

	count = 0;
	boolean = 0;
	while (*s)
	{
		if (*s != c && boolean == 0)
		{
			boolean = 1;
			count++;
		}
		else if (*s == c)
			boolean = 0;
		s++;
	}
	return (count);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**scan_list(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	j;
	int		word_start;

	i = 0;
	j = 0;
	word_start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && word_start < 0)
			word_start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && word_start >= 0)
		{
			strs[j] = fill_word(s, word_start, i);
			word_start = -1;
			j++;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	strs = scan_list((const char *)s, c, strs);
	return (strs);
}
