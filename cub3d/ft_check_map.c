/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:37:38 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 14:30:18 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *fname, t_param *p)
{
	char	*extension;
	char	tmp[5];
	int		i;

	extension = ".cub";
	i = strlen(fname) - 4;
	ft_strncpy(tmp, fname, i);
	if (ft_strncmp(extension, tmp, 5) != 0)
		put_error("Error\nAdd mapfile with \"*.cub\" extension!\n", p);
}

void	check_map(t_param *p, int x, int y)
{
	int		**map;

	map = p->map->worldmap;
	if (map[x][y] == 1 || map[x][y] == 3 || map[x][y] == 4)
		return ;
	if (x == 0 || y == 0 || x == p->map->max_x || y == p->map->max_y
		|| map[x][y] == -1)
	{
		ft_putstr_fd("Error\nMap not closed around spawn\nLine: ", 1);
		ft_putstr_fd(ft_itoa(p->map->first_line_map + x + 1), 1);
		ft_putstr_fd(" col: ", 1);
		ft_putstr_fd(ft_itoa(y + 1), 1);
		write(1, "\n", 1);
		close_game(p);
	}
	if (map[x][y] == 0)
		map[x][y] = 3;
	if (map[x][y] == 2)
		map[x][y] = 4;
	check_map(p, x + 1, y);
	check_map(p, x, y + 1);
	check_map(p, x - 1, y);
	check_map(p, x, y - 1);
}
