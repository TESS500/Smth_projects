/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:26:44 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 18:37:24 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_out;
	t_list	*elem;

	lst_out = NULL;
	while (lst)
	{
		if (!(ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&lst_out, del);
			return (NULL);
		}
		elem = ft_lstnew(f(lst->content));
		ft_lstadd_back(&lst_out, elem);
		lst = lst->next;
	}
	return (lst_out);
}
