/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:46:08 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 18:41:53 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, size_t pos_of_src)
{
	int	i;

	i = 0;
	if (strlen(src) < pos_of_src)
		return (0);
	while (src[pos_of_src] != '\0')
	{
		dest[i] = src[pos_of_src];
		i++;
		pos_of_src++;
	}
	dest[i] = '\0';
	return (dest);
}
