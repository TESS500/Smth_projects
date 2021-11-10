/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:41:13 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 16:22:10 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotation(t_player *pr)
{
	double	old_dir;
	double	old_plane;
	double	speed;

	old_dir = pr->dir_x;
	old_plane = pr->plane_x;
	speed = 0.02;
	if (pr->rightrot)
	{
		pr->dir_x = (pr->dir_x * cos(-speed) - pr->dir_y * sin(-speed));
		pr->dir_y = (old_dir * sin(-speed) + pr->dir_y * cos(-speed));
		pr->plane_x = (pr->plane_x * cos(-speed) - pr->plane_y * sin(-speed));
		pr->plane_y = (old_plane * sin(-speed) + pr->plane_y * cos(speed));
	}
	if (pr->leftrot)
	{
		pr->dir_x = (pr->dir_x * cos(speed) - pr->dir_y * sin(speed));
		pr->dir_y = (old_dir * sin(speed) + pr->dir_y * cos(speed));
		pr->plane_x = (pr->plane_x * cos(speed) - pr->plane_y * sin(speed));
		pr->plane_y = (old_plane * sin(speed) + pr->plane_y * cos(speed));
	}
}

int	can_move(int pos)
{
	if (pos == 1 || pos == 4)
		return (0);
	return (1);
}

void	move_updown(t_player *plr, t_world *map, float speed)
{
	if (plr->forward)
	{
		if (can_move(map->worldmap[(int)(plr->pos_x + plr->dir_x * speed)]
			[(int)(plr->pos_y)]))
			plr->pos_x += plr->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(plr->pos_x)]
			[(int)(plr->pos_y + plr->dir_y * speed)]))
			plr->pos_y += plr->dir_y * speed * 0.5;
	}
	if (plr->backward)
	{
		if (can_move(map->worldmap[(int)(plr->pos_x - plr->dir_x * speed)]
			[(int)(plr->pos_y)]))
			plr->pos_x -= plr->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(plr->pos_x)]
			[(int)(plr->pos_y - plr->dir_y * speed)]))
			plr->pos_y -= plr->dir_y * speed * 0.5;
	}
}

void	move_leftright(t_player *plr, t_world *map, float speed)
{
	if (plr->left)
	{
		if (can_move(map->worldmap[(int)(plr->pos_x)]
			[(int)(plr->pos_y + plr->dir_x * speed)]))
			plr->pos_y += plr->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(plr->pos_x - plr->dir_y * speed)]
			[(int)(plr->pos_y)]))
			plr->pos_x -= plr->dir_y * speed * 0.5;
	}
	if (plr->right)
	{
		if (can_move(map->worldmap[(int)(plr->pos_x)]
			[(int)(plr->pos_y - plr->dir_x * speed)]))
			plr->pos_y -= plr->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(plr->pos_x + plr->dir_y * speed)]
			[(int)(plr->pos_y)]))
			plr->pos_x += plr->dir_y * speed * 0.5;
	}
}

int	move(t_param *p)
{
	float	speed;

	speed = 0.2;
	move_updown(p->player, p->map, speed);
	move_leftright(p->player, p->map, speed);
	rotation(p->player);
	return (0);
}
