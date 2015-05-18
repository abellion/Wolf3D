# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abellion <abellion@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 21:03:07 by abellion          #+#    #+#              #
#    Updated: 2015/04/28 15:44:03 by abellion         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C =		gnl/get_next_line.c \
			srcs/main.c \
			srcs/parser_controller.c \
			srcs/player_controller.c \
			srcs/angle_controller.c \
			srcs/ray_controller.c \
			srcs/ray_utilities.c \
			srcs/draw_controller.c \
			srcs/draw_utilities.c \
			srcs/key_controller.c \
			srcs/key_move.c \
			srcs/env_controller.c \
			srcs/map_controller.c \

SOFT_NAME = wolf3d
OBJ = $(patsubst %.c, %.o, $(notdir $(SRC_C)))
C_G = $(shell echo "\033[0;32m")
C_END = $(shell echo "\033[0m")

FLAGS = -Wall -Wextra -Werror
INCLUDES = -I mlx_lib/ -I libft/includes/
LINKS = -L mlx_lib/ -lmlx -L libft/ -lft
FRAM = -framework OPENGL -framework AppKit

all: $(SOFT_NAME)

$(SOFT_NAME): $(SRC_C)
	make -C libft/
	make -C mlx_lib/
	@echo "\n$(C_G)	==========	SOFTWARE COMPILATION	==========$(C_END)"
	gcc -Ofast -g $(FLAGS) -c $(SRC_C) $(INCLUDES)
	@echo "\n$(C_G)	==========	CREATING EXECUTBLE FILE	==========$(C_END)"
	gcc -o $(SOFT_NAME) $(OBJ) $(LINKS) -Ofast $(FRAM)

clean:
	make -C libft/ clean
	make -C mlx_lib/ clean
	@echo "\n$(C_G)	==========	DELETING OBJECTS FILES	==========$(C_END)"
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	make -C mlx_lib/ clean
	@echo "\n$(C_G)	==========	DELETING SOFT FILE		==========$(C_END)"
	rm -rf $(SOFT_NAME)

re: fclean all
