/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:47:56 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/15 16:49:46 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fov_and_pos(t_mlx *mlx, t_world *map, t_ray *ray, t_player *plr)
{
	plr->camera_x = 2 * mlx->x / (double)mlx->screen_w - 1;
	ray->dir_x = plr->dir_x + plr->plane_x * plr->camera_x;
	ray->dir_y = plr->dir_y + plr->plane_y * plr->camera_x;
	map->x = (int)(plr->pos_x);
	map->y = (int)(plr->pos_y);
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
}

void	get_step(t_world *map, t_ray *ray, t_player *plr)
{
	if (ray->dir_x < 0)
	{
		map->step_x = -1;
		ray->side_x = (plr->pos_x - map->x) * ray->delta_x;
	}
	else
	{
		map->step_x = 1;
		ray->side_x = (map->x + 1.0 - plr->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		map->step_y = -1;
		ray->side_y = (plr->pos_y - map->y) * ray->delta_y;
	}
	else
	{
		map->step_y = 1;
		ray->side_y = (map->y + 1.0 - plr->pos_y) * ray->delta_y;
	}
}

void	wallhit(t_world *map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			map->x += map->step_x;
			ray->wallside = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			map->y += map->step_y;
			ray->wallside = 1;
		}
		if (map->worldmap[map->x][map->y] == 1)
			hit = 1;
	}
}

void	walldist_dir(t_mlx *mlx, t_world *map, t_player *plr, t_ray *ray)
{
	if (ray->wallside == 1)
	{
		if (map->y < plr->pos_y)
			ray->walldir = 'W';
		else
			ray->walldir = 'E';
		ray->walldist = (map->y - plr->pos_y
				+ (1 - map->step_y) / 2) / ray->dir_y;
		ray->wallx = plr->pos_x + ray->walldist * ray->dir_x;
	}
	else
	{
		if (map->x < plr->pos_x)
			ray->walldir = 'N';
		else
			ray->walldir = 'S';
		ray->walldist = (map->x - plr->pos_x
				+ (1 - map->step_x) / 2) / ray->dir_x;
		ray->wallx = plr->pos_y + ray->walldist * ray->dir_y;
	}
	ray->zbuffer[mlx->x] = ray->walldist;
}

void	raycast(t_mlx *mlx, t_player *plr, t_world *map, t_ray *ray)
{
	mlx->x = 0;
	while (mlx->x < mlx->screen_w)
	{
		fov_and_pos(mlx, map, ray, plr);
		get_step(map, ray, plr);
		wallhit(map, ray);
		walldist_dir(mlx, map, plr, ray);
		define_line(mlx, ray);
		choose_texture(mlx, ray);
		ray->wallx -= floor(ray->wallx);
		mlx->text_x = ray->wallx * (mlx->text_sl / 4);
		if (ray->wallside == 0 && ray->dir_x > 0)
			mlx->text_x = (mlx->text_sl / 4) - mlx->text_x - 1;
		else if (ray->wallside == 1 && ray->dir_y < 0)
			mlx->text_x = (mlx->text_sl / 4) - mlx->text_x - 1;
		draw_line(mlx, mlx->x, mlx->text_x);
		mlx->x++;
	}
}
