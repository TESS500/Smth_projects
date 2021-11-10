/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:47:18 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 14:30:27 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_lines(char **lines, char **tmp, int fd, int ret)
{
	char	*s;
	int		i;
	int		k;

	i = 1;
	while (ret)
	{
		ret = get_next_line(fd, &s);
		tmp = lines;
		k = 0;
		lines = malloc((i + 1) * sizeof(char *));
		i++;
		if (tmp)
		{
			while (tmp[k])
			{
				lines[k] = tmp[k];
				k++;
			}
		}
		free(tmp);
		lines[k++] = s;
		lines[k] = 0;
	}
	return (lines);
}

char	**parse_parameters(t_param *p, char **lines)
{
	int	i;
	int	j;
	int	map;

	i = 0;
	map = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (!choose_param(lines[i][j], lines[i], p))
		{
			p->map->first_line_map = i;
			return (&lines[i]);
		}
		i++;
	}
	put_error("Error\nNo map found\n", p);
	return (lines);
}

void	init_params(t_param *p)
{
	p->screen_done = 0;
	p->floor_done = 0;
	p->sky_done = 0;
	p->mlx->fr = -1;
	p->mlx->fg = -1;
	p->mlx->fb = -1;
	p->mlx->sr = -1;
	p->mlx->sg = -1;
	p->mlx->sb = -1;
	p->t1_done = 0;
	p->t2_done = 0;
	p->t3_done = 0;
	p->t4_done = 0;
	p->spr_done = 0;
}

void	verify_params(t_param *p)
{
	if (!(p->screen_done))
		put_error("Error\nNo resolution input\n", p);
	if (!(p->floor_done))
		put_error("Error\nNo floor color input\n", p);
	if (!(p->sky_done))
		put_error("Error\nNo ceiling color input\n", p);
	if (!p->t1_done || !p->t2_done || !p->t3_done
		|| !p->t4_done || !p->spr_done)
		put_error("Error\nMissing texture path\n", p);
}

int	parse_cub(char *fname, t_param *p)
{
	int		fd;
	char	**tmp;
	char	**maplines;

	tmp = NULL;
	check_extension(fname, p);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		put_error("Error\nMap file not found\n", p);
	p->lines = 0;
	p->lines = get_lines(p->lines, tmp, fd, 1);
	close(fd);
	init_params(p);
	maplines = parse_parameters(p, p->lines);
	verify_params(p);
	parse_map(p, maplines);
	p->mlx->sprites = get_sprites(p);
	return (1);
}
