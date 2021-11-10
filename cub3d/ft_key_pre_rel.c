/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_pre_rel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 18:19:59 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 16:21:56 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_param *p)
{
	if (key == 0)
		p->player->left = 1;
	else if (key == 1)
		p->player->backward = 1;
	else if (key == 2)
		p->player->right = 1;
	else if (key == 13)
		p->player->forward = 1;
	else if (key == 123)
		p->player->leftrot = 1;
	else if (key == 124)
		p->player->rightrot = 1;
	else if (key == 53)
		close_game(p);
	return (0);
}

int	key_release(int key, t_param *p)
{
	if (key == 0)
		p->player->left = 0;
	else if (key == 1)
		p->player->backward = 0;
	else if (key == 2)
		p->player->right = 0;
	else if (key == 13)
		p->player->forward = 0;
	else if (key == 123)
		p->player->leftrot = 0;
	else if (key == 124)
		p->player->rightrot = 0;
	return (0);
}
