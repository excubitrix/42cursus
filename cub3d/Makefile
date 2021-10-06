# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/01/23 21:39:31 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
LIBMLX = libmlx.a

RM = /bin/rm -f
RMDIR = /bin/rm -rf
BMP = bitmap.bmp
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(MLXDIR) -I$(INCDIR) -I$(LIBDIR)
LINKS = -L$(LIBDIR) -lft -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit

LIBDIR = ./libft/
MLXDIR = ./minilibx_opengl_20191021/

SRCDIR = ./srcs/
SRCS = $(addprefix $(SRCDIR), $(SRC))
SRC = main.c init.c parse.c parse_tools.c get_elem.c is_valid.c tools.c\
	hooks.c walls.c sprites.c draw_tools.c color_tools.c movement.c bitmap.c\
	queue_tools.c init_plr.c exit_tools.c

OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INCDIR = ./includes/
INCS = $(addprefix $(INCDIR), $(INC))
INC = cub3d.h bmp.h

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@$(MAKE) -C $(LIBDIR)
	@$(MAKE) -C $(MLXDIR)
	gcc $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

bonus:
	@$(MAKE) -C ./bonus/
	@cp ./bonus/$(NAME) ./$(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(BMP)
	@$(RMDIR) $(OBJDIR)
	@$(MAKE) -C ./bonus/ clean
	@$(MAKE) -C $(LIBDIR) clean
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C ./bonus/ fclean
	@$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
