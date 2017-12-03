# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbinet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 12:55:51 by cbinet            #+#    #+#              #
#    Updated: 2017/11/28 16:02:07 by cbinet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

MLX=mlx
MLX=minilibx
CC = gcc
CFLAGS = -framework OpenGL -framework AppKit -lmlx #-lXext -lX11
LFLAGS = -IGL -IGLUT -lXext -lX11 -lm
DEBUG = -ofast -o2 -flto -Wall -Wextra -Werror
DEBUG2 = -g -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
CPPFLAGS = -iquote includes/$(MLX) -iquote includes -iquote $(LIB_PATH)$(INC)

SRC_PATH = srcs/
SRC_NAME = fractol.c events.c move.c fractales.c draw.c series.c

OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = includes/
LIB_PATH := libft/
LIB := $(LIB_PATH)libftprintf.a  $(INC)$(MLX)/libmlx.a
LIB_INCLUDE := $(LIB_PATH)$(INC)libft.h			\
				$(LIB_PATH)$(INC)get_next_line.h\
				$(LIB_PATH)$(INC)ft_printf.h \
				$(INC)$(MLX)/mlx.h
HEADER := $(LIB_INCLUDE)						\
		 includes/fractol.h

all: lib $(NAME)

run: all
	./$(NAME)

$(NAME): $(OBJS)
	$(CC) $(DEBUG) $(OBJS) $(CPPFLAGS) $(LIB) $(LFLAGS)  -o $(NAME)
	@echo "\033[32m$(NAME) udpated\033[0m"

.PHONY:lib
lib:
	@make -C libft
	@make -C includes/$(MLX)
	
$(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) $(LIB)
	$(CC) $(DEBUG) $(CPPFLAGS) -c $< -o $@

.PHONY:clean
clean:
	@make clean -C libft
	@make clean -C includes/$(MLX)
	@rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files removed.\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "\033[31mBinary names removed.\033[0m"

re: fclean
	make
