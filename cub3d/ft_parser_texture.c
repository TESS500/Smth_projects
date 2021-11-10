/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:45:56 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 23:29:51 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_2(int dir, t_param *p)
{
	if (dir == 4)
	{
		if (p->t4_done)
			put_error("Error\nEAST Texture set more than once\n", p);
		else
			p->t4_done = 1;
	}
	if (dir == 5)
	{
		if (p->spr_done)
			put_error("Error\nSPRITE Texture set more than once\n", p);
		else
			p->spr_done = 1;
	}
}

void	check_texture(int dir, t_param *p)
{
	if (dir == 1)
	{
		if (p->t1_done)
			put_error("Error\nNORTH Texture set more than once\n", p);
		else
			p->t1_done = 1;
	}
	if (dir == 2)
	{
		if (p->t2_done)
			put_error("Error\nSOUTH Texture set more than once\n", p);
		else
			p->t2_done = 1;
	}
	if (dir == 3)
	{
		if (p->t3_done)
			put_error("Error\nWEST Texture set more than once\n", p);
		else
			p->t3_done = 1;
	}
	if (dir == 4 || dir == 5)
		check_texture_2(dir, p);
}

void	make_texture(int dir, char *str, t_param *p)
{
	int	fd;

	while (*str == ' ')
		str++;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		put_error("Error\nWrong texture path input\n", p);
	close(fd);
	if (dir == 1)
		p->mlx->txt->texture1_path = str;
	if (dir == 2)
		p->mlx->txt->texture2_path = str;
	if (dir == 3)
		p->mlx->txt->texture3_path = str;
	if (dir == 4)
		p->mlx->txt->texture4_path = str;
	if (dir == 5)
		p->mlx->txt->sprite_path = str;
	check_texture(dir, p);
}
