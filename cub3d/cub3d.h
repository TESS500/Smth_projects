/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:19:33 by ahokey            #+#    #+#             */
/*   Updated: 2021/04/19 14:06:44 by ahokey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx_opengl/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct s_textures
{
	void			*txt1_xpm_image;
	int				*txt1_data_addr;
	int				txt1_h;
	int				txt1_w;
	int				txt1_bpp;
	int				txt1_sl;
	int				txt1_edn;
	void			*txt2_xpm_image;
	int				*txt2_data_addr;
	int				txt2_h;
	int				txt2_w;
	int				txt2_bpp;
	int				txt2_sl;
	int				txt2_edn;
	void			*txt3_xpm_image;
	int				*txt3_data_addr;
	int				txt3_h;
	int				txt3_w;
	int				txt3_bpp;
	int				txt3_sl;
	int				txt3_edn;
	void			*txt4_xpm_image;
	int				*txt4_data_addr;
	int				txt4_h;
	int				txt4_w;
	int				txt4_bpp;
	int				txt4_sl;
	int				txt4_edn;
	void			*txt5_xpm_image;
	int				*txt5_data_addr;
	int				txt5_h;
	int				txt5_w;
	int				txt5_bpp;
	int				txt5_sl;
	int				txt5_edn;
	char			*texture1_path;
	char			*texture2_path;
	char			*texture3_path;
	char			*texture4_path;
	char			*sprite_path;
}					t_txt;

typedef struct s_spritepointer
{
	float			x;
	float			y;
}					t_sprptr;

typedef struct s_sprtools
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				sprscreenx;
	int				sprwidth;
	int				sprheight;
	int				drawstarty;
	int				drawendy;
	int				drawstartx;
	int				drawendx;
	int				spr_texture_x;
	int				spr_texture_y;
	int				x;
	int				y;
	int				d;
}					t_sprtools;

typedef struct s_mlx
{
	t_sprptr		*sprites;
	t_txt			*txt;
	void			*ptr;
	void			*win;
	void			*img;
	int				*d_ad;
	int				bpp;
	int				sl;
	int				edn;
	int				l_height;
	int				l_start;
	int				l_end;
	int				color;
	int				*txt_data;
	int				text_sl;
	int				text_h;
	int				text_x;
	int				screen_h;
	int				screen_w;
	int				x;
	int				*spr_order;
	int				spr_number;
	int				fr;
	int				fg;
	int				fb;
	int				sr;
	int				sg;
	int				sb;
}					t_mlx;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	char			forward;
	char			backward;
	char			left;
	char			right;
	char			leftrot;
	char			rightrot;
	int				spawn;
}					t_player;

typedef struct s_world
{
	int				**worldmap;
	int				**mapcopy;
	int				x;
	int				y;
	int				step_x;
	int				step_y;
	int				max_x;
	int				max_y;
	int				first_line_map;
}					t_world;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			walldist;
	double			spritedist;
	char			walldir;
	double			wallx;
	int				wallside;
	double			zbuffer[4000];
}					t_ray;

typedef struct s_param
{
	t_mlx			*mlx;
	t_player		*player;
	t_world			*map;
	t_ray			*ray;
	int				i;
	int				j;
	int				floor_done;
	int				screen_done;
	int				sky_done;
	int				t1_done;
	int				t2_done;
	int				t3_done;
	int				t4_done;
	int				spr_done;
	char			**lines;
	int				screenshot;
}					t_param;

int					atoi_floor_sky(const char *str);
int					atoi_resolution(const char *str);
void				check_extension(char *fname, t_param *p);
void				check_map(t_param *p, int x, int y);
void				check_player(t_param *p);
int					choose_param(char c, char *str, t_param *p);
void				choose_texture(t_mlx *mlx, t_ray *ray);
int					close_game(t_param *p);
void				define_line(t_mlx *mlx, t_ray *ray);
void				define_sprite_line(t_mlx *mlx, t_ray *ray);
int					draw_line(t_mlx *mlx, int x, int text_x);
void				draw_sprites(t_mlx *m, t_player *p, t_ray *r);
void				init_map(t_world *map, t_param *p);
t_sprptr			*get_sprites(t_param *p);
void				get_step(t_world *map, t_ray *ray, t_player *pl);
int					key_press(int key, t_param *p);
int					key_release(int key, t_param *p);
void				make_texture(int dir, char *str, t_param *p);
void				make_screenshot(t_param *p, char *str);
int					move(t_param *p);
void				move_leftright(t_player *pl, t_world *map, float speed);
void				move_updown(t_player *pl, t_world *map, float speed);
int					parse_cub(char *fname, t_param *p);
void				parse_map(t_param *p, char **maplines);
int					player_init(int x, int y, char dir, t_param *p);
void				put_error(char *message, t_param *p);
void				raycast(t_mlx *mlx, t_player *pl, t_world *map, t_ray *ray);
int					rgb_int(int red, int green, int blue);
void				rotation(t_player *pl);
int					run_game(t_param *p);
void				texture_init(t_txt *text, t_mlx *mlx);

#endif
