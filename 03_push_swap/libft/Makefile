# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 09:42:35 by floogman          #+#    #+#              #
#    Updated: 2021/04/13 12:50:50 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

RM = /bin/rm -f
RM_DIR = /bin/rm -rf
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
SRC = \
	ft_bzero.c \
	ft_calloc.c \
	ft_isdigit.c \
	ft_isspace.c \
	ft_max.c \
	ft_min.c \
	ft_putchar_fd.c \
	ft_putchar.c \
	ft_putendl_fd.c \
	ft_putnbr_endl.c \
	ft_putnbr_fd.c \
	ft_putnbr.c \
	ft_putstr_endl.c \
	ft_putstr_fd.c \
	ft_putstr.c \
	ft_strcmp.c \
	ft_strlen.c \
	ft_strncmp.c

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INC_DIR = ./includes/
INCS = $(addprefix $(INC_DIR), $(INC))
INC = libft.h

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ echo "\n\033[0;32mCompiling libft..."
	@ ar rc $(NAME) $(OBJS)
	@ ranlib $(NAME)
	@ echo "Done!\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@ printf "\033[0;33mGenerating object file %-33.33s\r" $@
	@ gcc $(CFLAGS) -c -I$(INC_DIR) -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@ $(RM) $(OBJS)
	@ $(RM_DIR) $(OBJ_DIR)

fclean: clean
	@ $(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
