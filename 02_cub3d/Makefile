# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/10/22 10:46:51 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I $(MLXDIR) -I $(INCDIR) -I $(LIBDIR) -c
LIBS = -L $(LIBDIR) -lft -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit

LIBDIR = ./libft/
LIBFT = libft.a

MLXDIR = ./minilibx_opengl_20191021/
LIBMLX = libmlx.a

BMP = bitmap.bmp

SRCDIR = ./srcs/
SRC = \
	bitmap.c \
	color_tools.c \
	draw_tools.c \
	exit_tools.c \
	get_elem.c \
	hooks.c \
	init_plr.c \
	init.c \
	is_valid.c \
	main.c \
	movement.c \
	parse_tools.c \
	parse.c \
	queue_tools.c \
	sprites.c \
	tools.c \
	walls.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./includes/
INC = cub3d.h bmp.h
INCS = $(addprefix $(INCDIR), $(INC))

# BONUS
BONUS = ./bonus/cub3D

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	@ $(MAKE) -C $(LIBDIR)
	@ $(MAKE) -C $(MLXDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@ $(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# BONUS
bonus: $(BONUS)

$(BONUS):
	@ $(MAKE) -C ./bonus/
	@ cp $(BONUS) $(NAME)

# MISC
clean:
	/bin/rm -rf $(OBJDIR)
	@ $(MAKE) -C ./bonus/ clean
	@ $(MAKE) -C $(LIBDIR) clean
	@ $(MAKE) -C $(MLXDIR) clean

fclean: clean
	/bin/rm -f $(NAME) $(BMP)
	@ $(MAKE) -C ./bonus/ fclean
	@ $(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
