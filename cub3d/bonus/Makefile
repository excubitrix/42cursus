# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/01/23 21:39:08 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
LIBMLX = libmlx.a

RM = /bin/rm -f
RMDIR = /bin/rm -rf
RES = native_res.txt
BMP = bitmap.bmp
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(MLXDIR) -I$(INCDIR) -I$(LIBDIR)
LINKS = -L$(LIBDIR) -lft -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit

LIBDIR = ../libft/
MLXDIR = ../minilibx_opengl_20191021/

SRCDIR = ./srcs/
SRCS = $(addprefix $(SRCDIR), $(SRC))
SRC = main.c init.c parse.c parse_tools.c get_elem.c is_valid.c tools.c\
	hooks.c floor_ceil_sky.c draw_tools.c color_tools.c movement.c bitmap.c\
	sprites.c walls.c doors.c sound.c hud.c hud_tools.c actions.c init_plr.c\
	wall_tools.c queue_tools.c exit_tools.c load_textures.c actions_tools.c

OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INCDIR = ./includes/
INCS = $(addprefix $(INCDIR), $(INC))
INC = cub3d.h bmp.h

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@$(RM) $(BMP)
	@$(MAKE) -C $(LIBDIR)
	@$(MAKE) -C $(MLXDIR)
	gcc $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	@$(RMDIR) $(OBJDIR)
	@$(MAKE) -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBDIR) fclean
	@$(MAKE) -C $(MLXDIR) clean

re: fclean all

.PHONY: all clean fclean re
