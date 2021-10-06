# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/10/06 12:47:09 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
LIBMLX = libmlx.a

BMP = bitmap.bmp
RES = native_res.txt

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I$(MLXDIR) -I$(INCDIR) -I$(LIBDIR) -c
LIBS = -L$(LIBDIR) -lft -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit

LIBDIR = ../libft/
MLXDIR = ../minilibx_opengl_20191021/

SRCDIR = ./srcs/
SRC = \
	actions_tools.c \
	actions.c \
	bitmap.c \
	color_tools.c \
	doors.c \
	draw_tools.c \
	exit_tools.c \
	floor_ceil_sky.c \
	get_elem.c \
	hooks.c \
	hud_tools.c \
	hud.c \
	init_plr.c \
	init.c \
	is_valid.c \
	load_textures.c \
	main.c \
	movement.c \
	parse_tools.c \
	parse.c \
	queue_tools.c \
	sound.c \
	sprites.c \
	tools.c \
	wall_tools.c \
	walls.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./includes/
INC = cub3d.h bmp.h
INCS = $(addprefix $(INCDIR), $(INC))

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

# MISC
clean:
	rm -rf $(OBJDIR)
	@ $(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME) $(BMP)
	@ $(MAKE) -C $(MLXDIR) clean
	@ $(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re
