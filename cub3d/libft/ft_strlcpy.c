/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:56:34 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 18:40:51 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i_src;

	i_src = 0;
	if (!dest || !src)
		return (0);
	while (src[i_src])
		i_src++;
	if (n == 0)
		return (i_src);
	i_src = 0;
	while (src[i_src] != '\0' && i_src < (n - 1))
	{
		dest[i_src] = src[i_src];
		i_src++;
	}
	dest[i_src] = '\0';
	i_src = 0;
	while (src[i_src])
		i_src++;
	return (i_src);
}
