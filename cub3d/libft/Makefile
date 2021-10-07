# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 09:42:35 by floogman          #+#    #+#              #
#    Updated: 2021/10/07 10:14:43 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I $(INCDIR) -c

SRCDIR = ./srcs/
SRC = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	\
	ft_delspace.c \
	\
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	\
	ft_itoa_base.c \
	ft_itoa.c \
	\
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	\
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memrcpy.c \
	ft_memset.c \
	\
	ft_putchar_fd.c \
	ft_putchar.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putnbr.c \
	ft_putstr_endl.c \
	ft_putstr_fd.c \
	ft_putstr.c \
	\
	ft_realloc.c \
	ft_split.c \
	\
	ft_strcat.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strndup.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	\
	ft_toupper.c \
	ft_tolower.c \
	\
	tab_free.c \
	\
	gnl/get_next_line_utils.c \
	gnl/get_next_line.c \
	\
	ft_printf/conv_cs.c \
	ft_printf/conv_di.c \
	ft_printf/conv_e.c \
	ft_printf/conv_f.c \
	ft_printf/conv_png.c \
	ft_printf/conv_ux.c \
	ft_printf/conv_ws.c \
	ft_printf/display_wchar.c \
	ft_printf/ft_printf.c \
	ft_printf/get.c \
	ft_printf/padding.c \
	ft_printf/tab.c \
	ft_printf/utils.c

OBJDIR = ./obj/
OBJDIR_GNL = $(OBJDIR)gnl/
OBJDIR_PRINTF = $(OBJDIR)ft_printf/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./includes/
INC = libft.h get_next_line.h ft_printf.h
INCS = $(addprefix $(INCDIR), $(INC))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR) $(OBJDIR_GNL) $(OBJDIR_PRINTF)

# MISC
clean:
	@ /bin/rm -rf $(OBJDIR) $(OBJDIR_GNL) $(OBJDIR_PRINTF)

fclean: clean
	@ /bin/rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
