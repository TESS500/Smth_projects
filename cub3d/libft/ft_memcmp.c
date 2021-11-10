/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:37:55 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 18:38:12 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n || (arr1 != NULL && arr2 == arr1))
		return (0);
	while ((((unsigned char *)arr1)[i] == ((unsigned char *)arr2)[i])
	&& (i < n - 1))
		i++;
	return (((unsigned char *)arr1)[i] - ((unsigned char *)arr2)[i]);
}
