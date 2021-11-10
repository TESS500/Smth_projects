/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:19:35 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 18:40:45 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	unsigned int	i_src;
	unsigned int	i_dest;
	unsigned int	i;

	i = 0;
	i_src = 0;
	i_dest = 0;
	while (src[i_src])
		i_src++;
	if (n == 0)
		return (i_src);
	while (i_dest < n && dest[i_dest])
		i_dest++;
	if (n <= i_dest)
		return (n + i_src);
	while (n && (--n - i_dest) && src[i])
	{
		dest[i_dest + i] = src[i];
		i++;
	}
	dest[i_dest + i] = '\0';
	return (i_src + i_dest);
}
