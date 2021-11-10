/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 02:50:46 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 23:45:06 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static unsigned int	ft_numstrs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static void	ft_makestr(char **str, unsigned int *len, char c)
{
	unsigned int	i;

	*str += *len;
	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	char			*str;
	unsigned int	len;
	unsigned int	count;
	unsigned int	i;

	if (!s)
		return (NULL);
	count = ft_numstrs(s, c);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!(arr))
		return (NULL);
	i = 0;
	len = 0;
	str = (char *)s;
	while (i++ < count)
	{
		ft_makestr(&str, &len, c);
		arr[i] = malloc(sizeof(char) * (len + 1));
		if (!(arr[i]))
			return (ft_free(arr));
		ft_strlcpy(arr[i], str, len + 1);
	}
	arr[i] = NULL;
	return (arr);
}
