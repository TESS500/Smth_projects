/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:35:52 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/17 22:55:16 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run_game(t_param *p)
{
	move(p);
	raycast(p->mlx, p->player, p->map, p->ray);
	draw_sprites(p->mlx, p->player, p->ray);
	if (!p->screenshot)
		mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, p->mlx->img, 0, 0);
	return (0);
}

int	close_game(t_param *p)
{
	int	i;

	i = 0;
	if (p->lines)
	{
		while (p->lines[i])
		{
			free(p->lines[i]);
			i++;
		}
		free(p->lines);
	}
	exit(1);
}

void	put_error(char *message, t_param *p)
{
	write(2, message, ft_strlen(message));
	close_game(p);
}

int	start_all(t_param *p, int ac, char **av)
{
	t_txt	text;

	p->mlx->txt = &text;
	parse_cub(av[1], p);
	p->mlx->ptr = mlx_init();
	if (!(p->mlx->ptr))
		put_error("Error\n Mlx function failed\n", p);
	texture_init(p->mlx->txt, p->mlx);
	p->mlx->img = mlx_new_image(p->mlx->ptr, p->mlx->screen_w,
			p->mlx->screen_h);
	p->mlx->d_ad = (int *)mlx_get_data_addr(p->mlx->img,
			&(p->mlx->bpp), &(p->mlx->sl), &(p->mlx->edn));
	if (ac == 3)
		make_screenshot(p, av[2]);
	p->mlx->win = mlx_new_window(p->mlx->ptr, p->mlx->screen_w,
			p->mlx->screen_h, "cub3d");
	if (!(p->mlx->win))
		put_error("Error\n Mlx function failed\n", p);
	mlx_hook(p->mlx->win, 2, 1, key_press, (void *)p);
	mlx_key_hook(p->mlx->win, key_release, (void *)p);
	mlx_hook(p->mlx->win, 17, 1, close_game, (void *)p);
	mlx_loop_hook(p->mlx->ptr, run_game, (void *)p);
	mlx_loop(p->mlx->ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_player	one;
	t_world		map;
	t_ray		ray;
	t_param		p;

	p.mlx = &mlx;
	p.player = &one;
	p.map = &map;
	p.ray = &ray;
	p.lines = 0;
	if (ac > 3)
		put_error("Error\nToo many arguments\n", &p);
	if (ac < 2)
		put_error("Error\nNot enough arguments\n", &p);
	start_all(&p, ac, av);
}
