# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 16:02:55 by anikoyan          #+#    #+#              #
#    Updated: 2025/06/26 16:05:43 by anikoyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = fractol

# Source files
SRC = main.c init.c render.c math_utils.c events.c

# Object files directory and list
# This creates a list of .o files in the obj/ directory from the .c files
OBJDIR = obj
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# --- LIBRARIES ---

# Libft configuration
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# MiniLibX configuration
MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

# --- FLAGS & INCLUDES ---

# Include paths for all header files (.h)
# We need to tell the compiler where to find fractol.h (.), libft headers, and mlx.h
INC = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

# Linker flags required by MiniLibX on macOS
MLX_FLAGS = -framework OpenGL -framework AppKit

# --- MAKE RULES ---

# The 'all' rule is the default goal. It now depends on creating the object directory first.
all: $(OBJDIR) $(NAME)

# Rule to link the final executable
# It depends on the object files and both static library files (.a)
$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB)
	# This command links all the object files and libraries together to create the final executable.
	# We provide the direct paths to our static libraries, which is more reliable.
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS)

# Rule to create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to compile each source file (.c) into an object file (.o)
# '$<' is an automatic variable for the dependency (the .c file)
# '$@' is an automatic variable for the target (the .o file)
$(OBJDIR)/%.o: %.c fractol.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Rule to build the libft library by running 'make' in its directory
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Rule to build the MiniLibX library by running 'make' in its directory
$(MLX_LIB):
	make -C $(MLX_DIR)

# --- CLEANING RULES ---

# Rule to clean up object files and library build artifacts
clean:
	$(RM) -r $(OBJDIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

# Rule to clean everything, including the final executable and library archives
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	# MiniLibX's 'make clean' usually removes the .a file, so a specific fclean is often not needed for it.

# Rule to force a complete rebuild from scratch
re: fclean all

# Phony targets are rules that don't represent actual files on disk
.PHONY: all clean fclean re
