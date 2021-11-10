/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:45:22 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 13:28:32 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_sprites(t_world *map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	count = 0;
	while (x < map->max_x)
	{
		y = 0;
		while (y < map->max_y)
		{
			if (map->worldmap[x][y] == 4)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

t_sprptr	*get_sprites(t_param *p)
{
	t_sprptr	*sprites;
	int			x;
	int			y;
	int			i;

	p->mlx->spr_number = count_sprites(p->map);
	sprites = (malloc(p->mlx->spr_number * sizeof(t_sprptr)));
	p->mlx->spr_order = (malloc(p->mlx->spr_number * sizeof(int)));
	x = 0;
	i = 0;
	while (x < p->map->max_x)
	{
		y = 0;
		while (y < p->map->max_y)
		{
			if (p->map->worldmap[x][y] == 4)
			{
				sprites[i].x = x;
				sprites[i++].y = y;
			}
			y++;
		}
		x++;
	}
	return (sprites);
}
