# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 20:03:01 by lzaccome          #+#    #+#              #
#    Updated: 2022/07/01 00:40:22 by lzaccome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

CFLAGS =  -Wall -Wextra -Werror

# CFLAGS += -fsanitize=address -g3

SRCS =	srcs/main.c \
		srcs/parse.c \
		srcs/gnl_utils.c \
		srcs/get_next_line.c \
		srcs/error.c \
		srcs/utils.c \
		srcs/mini_map.c \
		srcs/direction.c

_GREY=	$'\033[1;30m
_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_YELLOW=$'\033[1;33m
_BLUE=	$'\033[1;34m
_PURPLE=$'\033[1;35m
_CYAN=	$'\033[1;36m
_WHITE=	$'\033[1;37m

OBJ = $(SRCS:.c=.o)
MLX = -lmlx -Lmlx_linux -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ)
		@echo "$(_YELLOW)[Compilation ongoing ...]"
		@echo "$(_GREEN)[Compilation finished]"
		@make -C mlx_linux all
			$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)
		@echo "$(_CYAN)[Executable created]"
		@echo [Name : cub3D]

%o: %.c
	$(CC) $(FLAGS) -I includes -Imlx_linux -O3 -c $< -o $@
	
clean:
	@rm -f $(OBJ)
	@echo "$(_RED)[All .o removed]"

fclean: clean
	@rm -f $(NAME)
	@echo "$(_RED)[Executable removed]"

git : fclean
	git add --all
	git commit 
	git push 
	
re: fclean all

.PHONY : all bonus clean fclean re