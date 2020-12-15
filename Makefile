# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/04 02:05:35 by sdonya            #+#    #+#              #
#    Updated: 2020/07/04 02:05:41 by sdonya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#    PROJECT    #
NAME = fractol

#    DIRECTORIES    #
SRC_DIR = ./src/
LIB_DIR = ./libft
MLX_DIR = ./minilibx_macos/
OBJ_DIR = ./obj
SRC_INC_DIR = ./includes
LIB_INC_DIR = ./libft/includes
MLX_INC_DIR = ./minilibx_macos/

#    FLAGS    #
CFLGS = -Wall -Werror -Wextra -lm -lmlx -framework OpenGL -framework AppKit
LFLGS = -L$(LIB_DIR) -lft
MLXFLGS = -L$(MLX_DIR) -lft
CC = gcc

#    LIBFT    #
LIBFT = $(LIB_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

#    SOURCES AND HEADERS    #
SRC_FILES =  main.c hook.c mandelbrot.c julia.c tools.c burningship.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

#    INCLUDES    #
INCL = -I$(SRC_INC_DIR) -I$(LIB_INC_DIR) -I$(MLX_INC_DIR)

#    RULES    #
.PHONY: all clean fclean re

all: $(NAME)

-include: $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLGS) -c -o $@ $< $(INCL)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLGS) -o $(NAME) $(OBJS) $(INCL) $(LFLGS)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
