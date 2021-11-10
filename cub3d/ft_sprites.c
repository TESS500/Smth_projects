/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:49:48 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/18 00:22:20 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_mlx *mlx, t_player *plr, int i)
{
	double		distance[1000];
	int			tmp;
	int			disttmp;

	while (++i < mlx->spr_number)
	{
		distance[i] = ((plr->pos_x - mlx->sprites[i].x) * (plr->pos_x
					- mlx->sprites[i].x) + (plr->pos_y - mlx->sprites[i].y)
				* (plr->pos_y - mlx->sprites[i].y));
		mlx->spr_order[i] = i;
	}
	i = -1;
	while (++i < mlx->spr_number - 1)
	{
		if (distance[i] < distance[i + 1])
		{
			disttmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = disttmp;
			tmp = mlx->spr_order[i];
			mlx->spr_order[i] = mlx->spr_order[i + 1];
			mlx->spr_order[i + 1] = tmp;
			i = -1;
		}
	}
}

void	sprite_height(t_sprtools *sprite, t_mlx *mlx)
{
	sprite->sprheight = abs((int)(mlx->screen_h / (sprite->transformy)));
	sprite->drawstarty = -sprite->sprheight / 2 + mlx->screen_h / 2;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->sprheight / 2 + mlx->screen_h / 2;
	if (sprite->drawendy >= mlx->screen_h)
		sprite->drawendy = mlx->screen_h;
}

void	sprite_width(t_sprtools *sprite, t_mlx *mlx)
{
	sprite->sprwidth = abs((int)(mlx->screen_h / (sprite->transformy)));
	sprite->drawstartx = -sprite->sprwidth / 2 + sprite->sprscreenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->sprwidth / 2 + sprite->sprscreenx;
	if (sprite->drawendx >= mlx->screen_w)
		sprite->drawendx = mlx->screen_w;
}

void	draw_spritelines(t_sprtools *spr, t_mlx *mlx, t_ray *ray)
{
	spr->x = spr->drawstartx;
	while (spr->x < spr->drawendx)
	{
		spr->spr_texture_x = (int)((spr->x - (-spr->sprwidth / 2
						+ spr->sprscreenx)) * mlx->txt->txt5_w / spr->sprwidth);
		spr->y = spr->drawstarty;
		if (spr->transformy > 0 && spr->x >= 0 && spr->x
			< mlx->screen_w && spr->transformy < (float)ray->zbuffer[spr->x])
		{
			while (spr->y < spr->drawendy)
			{
				spr->d = (spr->y) * 256 - mlx->screen_h * 128
					+ spr->sprheight * 128;
				spr->spr_texture_y = ((spr->d * mlx->txt->txt5_h)
						/ spr->sprheight) / 256;
				if (*(mlx->txt->txt5_data_addr + spr->spr_texture_x
						+ spr->spr_texture_y * mlx->txt->txt5_sl / 4))
					*(mlx->d_ad + spr->x + spr->y * mlx->sl / 4)
						= *(mlx->txt->txt5_data_addr + spr->spr_texture_x
							+ spr->spr_texture_y * mlx->txt->txt5_sl / 4);
				spr->y++;
			}
		}
		spr->x++;
	}
}

void	draw_sprites(t_mlx *mlx, t_player *pl, t_ray *ray)
{
	int			i;
	t_sprptr	sprite_ptr;
	t_sprtools	sprite;

	sort_sprites(mlx, pl, -1);
	i = 0;
	while (i < mlx->spr_number)
	{
		sprite_ptr = mlx->sprites[mlx->spr_order[i++]];
		sprite.spritex = (sprite_ptr.x + 0.5) - pl->pos_x;
		sprite.spritey = (sprite_ptr.y + 0.5) - pl->pos_y;
		sprite.invdet = 1.0 / (pl->plane_x * pl->dir_y
				- pl->dir_x * pl->plane_y);
		sprite.transformx = sprite.invdet * (pl->dir_y
				* sprite.spritex - pl->dir_x * sprite.spritey);
		sprite.transformy = sprite.invdet
			* (-pl->plane_y * sprite.spritex + pl->plane_x * sprite.spritey);
		sprite.sprscreenx = (int)((mlx->screen_w / 2)
				* (1 + sprite.transformx / sprite.transformy));
		sprite_height(&sprite, mlx);
		sprite_width(&sprite, mlx);
		draw_spritelines(&sprite, mlx, ray);
	}
}
