/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:16:05 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 23:43:00 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void			*mass;

	if (!num || !size)
	{
		num = 1;
		size = 1;
	}
	mass = malloc(num * size);
	if (!(mass))
		return (0);
	ft_bzero(mass, num * size);
	return (mass);
}
