/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 07:09:13 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 23:43:31 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	while (nbr >= 10)
	{
		nbr /= 10;
		i++;
	}
	return (i + 1);
}

static char	*ft_itoa_tail(char *str, unsigned int len, unsigned int n)
{
	unsigned int	i;

	i = len - 1;
	while (n >= 10)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	str[i] = n % 10 + 48;
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	int				a;

	a = 0;
	if (n < 0)
	{
		a = 1;
		n *= -1;
	}
	len = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * len + 1 + a);
	if (!(str))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		len++;
	}
	return (ft_itoa_tail(str, len, n));
}
