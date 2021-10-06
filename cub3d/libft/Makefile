# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 09:42:35 by floogman          #+#    #+#              #
#    Updated: 2021/01/23 21:33:07 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

RM = /bin/rm -f
RM_DIR = /bin/rm -rf
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memrcpy.c ft_memccpy.c ft_memmove.c\
	ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c\
	ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c\
	ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c ft_toupper.c\
	ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c\
	ft_split.c ft_itoa.c ft_strmapi.c ft_putchar.c ft_putchar_fd.c\
	ft_putendl_fd.c ft_putstr.c ft_putstr_fd.c ft_putstr_endl.c ft_putnbr.c\
	ft_putnbr_fd.c ft_isspace.c ft_strcat.c ft_strcmp.c ft_strndup.c\
	ft_itoa_base.c ft_realloc.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
	ft_lstmap.c\
	gnl/get_next_line.c gnl/get_next_line_utils.c\
	ft_printf/ft_printf.c ft_printf/conv_cs.c ft_printf/conv_di.c\
	ft_printf/conv_e.c ft_printf/conv_f.c ft_printf/conv_ux.c\
	ft_printf/conv_ws.c ft_printf/dispatcher_png.c ft_printf/display_wchar.c\
	ft_printf/get.c ft_printf/padding.c ft_printf/tab.c ft_printf/tools.c\
	tab_free.c ft_delspace.c

OBJ_DIR = ./obj/
OBJ_DIR_GNL = $(OBJ_DIR)gnl/
OBJ_DIR_PRINTF = $(OBJ_DIR)ft_printf/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INC_DIR = ./includes/
INCS = $(addprefix $(INC_DIR), $(INC))
INC = libft.h get_next_line.h ft_printf.h

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	gcc $(CFLAGS) -c -I$(INC_DIR) -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_GNL)
	@mkdir -p $(OBJ_DIR_PRINTF)

clean:
	@$(RM) $(OBJS)
	@$(RM_DIR) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
