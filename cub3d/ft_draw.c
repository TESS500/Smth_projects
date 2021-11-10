/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:39:07 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 16:20:41 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	draw_line(t_mlx *mlx, int x, int text_x)
{
	int		i;
	int		*text;
	double	step;
	double	pos;

	i = -1;
	step = 1.0 * mlx->text_h / mlx->l_height;
	pos = (mlx->l_start - mlx->screen_h / 2 + mlx->l_height / 2) * step;
	text = mlx->txt_data;
	while (++i < mlx->l_start)
	{
		*(mlx->d_ad + x + i * mlx->sl / 4) = rgb_int(mlx->sr, mlx->sg, mlx->sb);
	}
	while (i <= mlx->l_end)
	{
		*(mlx->d_ad + x + (i++) * mlx->sl / 4)
			= *(text + text_x + (int)pos * mlx->text_sl / 4);
		pos += step;
	}
	while (i < mlx->screen_h)
		*(mlx->d_ad + x + (i++) * mlx->sl / 4)
			= rgb_int(mlx->fr, mlx->fg, mlx->fb);
	return (1);
}

void	define_line(t_mlx *mlx, t_ray *ray)
{
	mlx->l_height = (int)(mlx->screen_h / ray->walldist);
	mlx->l_start = (mlx->l_height * -1) / 2 + mlx->screen_h / 2;
	if (mlx->l_start < 0)
		mlx->l_start = 0;
	mlx->l_end = mlx->l_height / 2 + mlx->screen_h / 2;
	if (mlx->l_end >= mlx->screen_h)
		mlx->l_end = mlx->screen_h - 1;
}

void	choose_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->walldir == 'N')
	{
		mlx->txt_data = mlx->txt->txt1_data_addr;
		mlx->text_sl = mlx->txt->txt1_sl;
		mlx->text_h = mlx->txt->txt1_h;
	}
	else if (ray->walldir == 'S')
	{
		mlx->txt_data = mlx->txt->txt2_data_addr;
		mlx->text_sl = mlx->txt->txt2_sl;
		mlx->text_h = mlx->txt->txt2_h;
	}
	else if (ray->walldir == 'E')
	{
		mlx->txt_data = mlx->txt->txt3_data_addr;
		mlx->text_sl = mlx->txt->txt3_sl;
		mlx->text_h = mlx->txt->txt3_h;
	}
	else
	{
		mlx->txt_data = mlx->txt->txt4_data_addr;
		mlx->text_sl = mlx->txt->txt4_sl;
		mlx->text_h = mlx->txt->txt4_h;
	}
}
