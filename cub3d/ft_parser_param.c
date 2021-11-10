/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:43:34 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 10:37:53 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extra_error(char *str, t_param *p, char *message)
{
	while (ft_isdigit(*str))
		str++;
	while (*str == ' ')
		str++;
	if (*str)
		put_error(message, p);
}

void	make_resolution(char *str, t_param *p)
{
	int		x;
	int		y;

	if (p->screen_done)
		put_error("Error\nMultiple resolution inputs\n", p);
	p->screen_done = 1;
	while (*str == ' ')
		str++;
	p->mlx->screen_w = atoi_resolution(str);
	while (ft_isdigit(*str))
		str++;
	if (*str != ' ')
		put_error("Error\nWrong resolution input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->screen_h = atoi_resolution(str);
	extra_error(str, p, "Error\nToo many resolution inputs\n");
	if (p->mlx->screen_h <= 0 || p->mlx->screen_w <= 0)
		put_error("Error\nIncorrect resolution values\n", p);
	mlx_get_screen_size(&x, &y);
	if (p->mlx->screen_h > y)
		p->mlx->screen_h = y;
	if (p->mlx->screen_w > x)
		p->mlx->screen_w = x;
}

void	make_floor(char *str, t_param *p)
{
	if (p->floor_done)
		put_error("Error\nMultiple floor color inputs\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fr = atoi_floor_sky(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("Error\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fg = atoi_floor_sky(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("Error\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fb = atoi_floor_sky(str);
	if (p->mlx->fr == -1 || p->mlx->fg == -1 || p->mlx->fb == -1)
		put_error("Error\nWrong values for floor color\n", p);
	extra_error(str, p, "Error\nToo many resolution inputs\n");
	p->floor_done = 1;
}

void	make_sky(char *str, t_param *p)
{
	if (p->sky_done)
		put_error("Error\nMultiple ceiling color inputs\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sr = atoi_floor_sky(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("Error\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sg = atoi_floor_sky(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("Error\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sb = atoi_floor_sky(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*str || p->mlx->sb == -1 || p->mlx->sr == -1 || p->mlx->sg == -1)
		put_error("Error\nWrong values for ceiling color\n", p);
	p->sky_done = 1;
}

int	choose_param(char c, char *str, t_param *p)
{
	while (*str == ' ')
		str++;
	if (c == 'R' && *(str + 1) == ' ')
		make_resolution(str + 1, p);
	else if (c == 'F' && *(str + 1) == ' ')
		make_floor(str + 1, p);
	else if (c == 'C' && *(str + 1) == ' ')
		make_sky(str + 1, p);
	else if (c == 'N' && *(str + 1) == 'O' && *(str + 2) == ' ')
		make_texture(1, str + 2, p);
	else if (c == 'S' && *(str + 1) == 'O' && *(str + 2) == ' ')
		make_texture(2, str + 2, p);
	else if (c == 'W' && *(str + 1) == 'E' && *(str + 2) == ' ')
		make_texture(4, str + 2, p);
	else if (c == 'E' && *(str + 1) == 'A' && *(str + 2) == ' ')
		make_texture(3, str + 2, p);
	else if (c == 'S' && *(str + 1) == ' ')
		make_texture(5, str + 1, p);
	else if (c == '1' || c == '0' || c == '2')
		return (0);
	else if (c)
		put_error("Error\nNon-empty line with wrong identifier\n", p);
	return (1);
}
