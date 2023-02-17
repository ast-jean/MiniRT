/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:45:28 by ast-jean          #+#    #+#             */
/*   Updated: 2022/07/18 11:15:56 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	t_list	*begin;

	if (lst)
	{
		temp = lst;
		begin = ft_lstnew(f(temp->content));
		if (!(begin))
			return (NULL);
		temp = temp->next;
		while (temp)
		{
			new = ft_lstnew(f(temp->content));
			if (!(new))
			{
				ft_lstclear(&begin, del);
				return (NULL);
			}
			ft_lstadd_back(&begin, new);
			temp = temp->next;
		}
		return (begin);
	}
	return (NULL);
}
