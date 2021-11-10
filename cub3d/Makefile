# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahokey <ahokey@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 15:07:08 by ahokey            #+#    #+#              #
#    Updated: 2021/04/19 12:27:34 by ahokey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= cub3D
MLX		= -lmlx -lm -framework OpenGL -framework AppKit
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I mlx_opengl/ -I libft/
FLAG 	= -Wall -Wextra -Werror

SRC =	cub3d.c\
		ft_check_map.c\
		ft_draw.c\
		ft_flo_sky_res.c\
		ft_init.c\
		ft_key_pre_rel.c\
		ft_move.c\
		ft_parser_map.c\
		ft_parser_param.c\
		ft_parser_sprite.c\
		ft_parser_texture.c\
		ft_parser.c\
		ft_rays.c\
		ft_screenshot.c\
		ft_sprites.c

OBJ = $(SRC:.c=.o) 

$(NAME) : $(OBJ)
	@echo "\033[33m[Libft compilation...]"
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./mlx_opengl
	@echo "\033[33m[Cub3D compilation...]"
	@gcc $(FLAG) $(OBJ) $(MLX) ./libft/libft.a ./mlx_opengl/libmlx.a -o $(NAME)
	@echo "\033[33m[Done !]"

all : $(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C ./libft
fclean : clean
	$(MAKE) fclean -C ./libft
	$(MAKE) clean -C ./mlx_opengl
	rm -rf $(NAME)
	rm -rf screenshot_cub3d.bmp

re : fclean all
	
%.o: %.c cub3d.h
	gcc $(FLAG) $(INCLUDE) -c $<  -o $(<:.c=.o)

.PHONY:	clean fclean re 