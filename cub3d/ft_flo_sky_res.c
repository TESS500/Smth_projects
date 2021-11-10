/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flo_sky_res.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:36:50 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 16:21:01 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_numlen(const char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	return (i);
}

int	atoi_resolution(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (ft_numlen(str) > 4)
		return (7680);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			break ;
	}
	return ((int)(n));
}

int	atoi_floor_sky(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (ft_numlen(str) > 3)
		return (-1);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			break ;
	}
	if (n < 0 || n > 255)
		return (-1);
	return ((int)(n));
}
