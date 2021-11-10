/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:50:56 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 18:41:43 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = 0;
	while (str[i])
	{
		if (str[i] == ch)
			tmp = (char *)&str[i];
		i++;
	}
	if (ch == str[i])
		return ((char *)&str[i]);
	return (tmp);
}
