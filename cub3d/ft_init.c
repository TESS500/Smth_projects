/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:40:15 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 13:27:07 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_init(t_txt *text, t_mlx *mlx)
{
	text->txt1_xpm_image = mlx_xpm_file_to_image(mlx->ptr,
			text->texture1_path, &(text->txt1_w), &(text->txt1_h));
	text->txt2_xpm_image = mlx_xpm_file_to_image(mlx->ptr,
			text->texture2_path, &(text->txt2_w), &(text->txt2_h));
	text->txt3_xpm_image = mlx_xpm_file_to_image(mlx->ptr,
			text->texture3_path, &(text->txt3_w), &(text->txt3_h));
	text->txt4_xpm_image = mlx_xpm_file_to_image(mlx->ptr,
			text->texture4_path, &(text->txt4_w), &(text->txt4_h));
	text->txt5_xpm_image = mlx_xpm_file_to_image(mlx->ptr,
			text->sprite_path, &(text->txt5_w), &(text->txt5_h));
	text->txt1_data_addr = (int *)mlx_get_data_addr(text->txt1_xpm_image,
			&text->txt1_bpp, &text->txt1_sl, &text->txt1_edn);
	text->txt2_data_addr = (int *)mlx_get_data_addr(text->txt2_xpm_image,
			&text->txt2_bpp, &text->txt2_sl, &text->txt2_edn);
	text->txt3_data_addr = (int *)mlx_get_data_addr(text->txt3_xpm_image,
			&text->txt3_bpp, &text->txt3_sl, &text->txt3_edn);
	text->txt4_data_addr = (int *)mlx_get_data_addr(text->txt4_xpm_image,
			&text->txt4_bpp, &text->txt4_sl, &text->txt4_edn);
	text->txt5_data_addr = (int *)mlx_get_data_addr(text->txt5_xpm_image,
			&text->txt5_bpp, &text->txt5_sl, &text->txt5_edn);
}

void	set_camera_ns(char dir, t_player *player)
{
	if (dir == 'N')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	set_camera_we(char dir, t_player *player)
{
	if (dir == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
}

int	player_init(int x, int y, char dir, t_param *p)
{
	p->player->pos_x = x + 0.5;
	p->player->pos_y = y + 0.5;
	if (dir == 'N' || dir == 'S')
		set_camera_ns(dir, p->player);
	else
		set_camera_we(dir, p->player);
	p->player->forward = 0;
	p->player->backward = 0;
	p->player->left = 0;
	p->player->right = 0;
	p->player->rightrot = 0;
	p->player->leftrot = 0;
	return (1);
}

void	init_map(t_world *map, t_param *p)
{
	int	i;
	int	j;

	i = 0;
	map->worldmap = malloc((map->max_x + 1) * sizeof(int *));
	if (!(map->worldmap))
		put_error("Error\nMalloc failed\n", p);
	while (i <= map->max_x)
	{
		map->worldmap[i] = malloc((map->max_y + 1) * sizeof(int));
		if (!(map->worldmap[i]))
			put_error("Error\nMalloc failed\n", p);
		j = 0;
		while (j <= map->max_y)
		{
			map->worldmap[i][j] = -1;
			j++;
		}
		i++;
	}
}
