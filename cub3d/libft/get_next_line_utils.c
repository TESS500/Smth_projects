/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:08:22 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 23:53:11 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_n(char *str)
{
	char	*check;

	if (!str)
		return (NULL);
	check = str;
	while (*check)
	{
		if (*check == '\n')
			return (check);
		check++;
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	dup = (char *)malloc(sizeof(*str) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(*s1) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	free((void *)s1);
	return (new);
}
