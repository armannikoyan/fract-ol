# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 17:33:27 by anikoyan          #+#    #+#              #
#    Updated: 2024/07/23 17:45:45 by anikoyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = main.c init.c render.c math_utils.c events.c

OBJDIR = obj
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a
MLX_INC = -Lminilibx -lmlx -framework OpenGL -framework AppKit
INC = -I $(MLX_DIR)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I $(LIBFT_DIR)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c fractol.h
	$(CC) $(CFLAGS) $(INC) $(LIBFT_INC) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(OBJ) $(LIBFT) $(MLX) $(MLX_INC) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJDIR) 2>/dev/null || true
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
