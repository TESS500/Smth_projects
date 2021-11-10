/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:30:12 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 23:53:59 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_return(char *var, int rtrn)
{
	free(var);
	return (rtrn);
}

char	*ft_remainder(char *mem)
{
	char		*tmp;
	int			size;
	int			i;

	size = 0;
	i = 0;
	while (mem[size] != '\n' && mem[size] != '\0')
		size++;
	if (mem[size] == '\0')
	{
		free(mem);
		return (0);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(mem) - size + 1));
	if (!(tmp))
		return (NULL);
	size++;
	while (mem[size] != '\0')
		tmp[i++] = mem[size++];
	tmp[i] = '\0';
	free(mem);
	return (tmp);
}

char	*ft_get_line(const char *mem)
{
	char		*tmp;
	int			size;
	int			i;

	size = 0;
	if (mem[size] == '\n' || mem[size] == '\0')
		return (ft_strdup(""));
	else
		while (*mem && mem[size] != '\0' && mem[size] != '\n')
			size++;
	tmp = malloc(sizeof(char) * (size + 1));
	if (!(tmp))
		return (NULL);
	i = 0;
	while (i < size)
	{
		tmp[i] = mem[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	static char	*mem[10000];
	char		*buf;
	int			byte_was_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !buf)
		return (-1);
	if (!mem[fd])
		mem[fd] = ft_strdup("");
	byte_was_read = 1;
	while (!(ft_strchr_n(mem[fd])) && byte_was_read != 0)
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		if (byte_was_read == -1)
			return (ft_return (mem[fd], -1));
		buf[byte_was_read] = '\0';
		mem[fd] = ft_strjoin(mem[fd], buf);
	}
	free(buf);
	*line = ft_get_line(mem[fd]);
	mem[fd] = ft_remainder(mem[fd]);
	if (byte_was_read)
		return (1);
	return (0);
}
