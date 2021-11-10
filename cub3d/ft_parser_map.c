/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:42:58 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 13:28:10 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_symbol(int value, int x, int y, t_param *p)
{
	if (value != 'N' && value != 'W'
		&& value != 'S' && value != 'E'
		&& value != '0' && value != '1'
		&& value != '2')
	{
		ft_putstr_fd("Error\nMap contains an invalid symbol: ", 1);
		write(1, &value, 1);
		write(1, "\n", 1);
		close_game(p);
	}
	if (value == 'N' || value == 'W'
		|| value == 'S' || value == 'E')
	{
		if (p->player->spawn == 0)
		{
			p->player->spawn = 1;
			player_init(x, y, value, p);
		}
		else
			put_error("Error\nMultiple spawnpoints set\n", p);
	}
}

void	make_map(char **lines, t_world *map, t_param *p)
{
	int		i;
	int		j;

	p->player->spawn = 0;
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == ' ')
				lines[i][j] = '0';
			check_map_symbol(lines[i][j], i, j, p);
			map->worldmap[i][j] = lines[i][j] - 48;
			j++;
		}
		i++;
	}
	if (p->player->spawn == 0)
		put_error("Error\nNo spawnpoint\nAdd 'N'/'S'/'E' or 'W' to map\n", p);
}

int	get_max_x(char **lines, t_param *p)
{
	int		i;
	int		j;
	int		emptyline;

	i = 0;
	emptyline = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (!lines[i][j])
			emptyline = 1;
		if (lines[i][j] && emptyline)
			put_error("Error\nAdditional input after map\n", p);
		i++;
	}
	return (i);
}

int	get_max_y(char **lines)
{
	int	i;
	int	j;
	int	max_y;

	i = 0;
	j = 0;
	max_y = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
			j++;
		if (j > max_y)
			max_y = j;
		i++;
	}
	return (max_y);
}

void	parse_map(t_param *p, char **maplines)
{
	p->map->max_x = get_max_x(maplines, p);
	p->map->max_y = get_max_y(maplines);
	init_map(p->map, p);
	make_map(maplines, p->map, p);
	check_map(p, p->player->pos_x, p->player->pos_y);
}
