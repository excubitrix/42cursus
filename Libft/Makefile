# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 09:42:35 by floogman          #+#    #+#              #
#    Updated: 2021/10/07 10:07:17 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
BONUS = $(BNSDIR)bonus.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I $(INCDIR) -c

INCDIR = ./includes/
INC = libft.h
INCS = $(addprefix $(INCDIR), $(INC))

SRCDIR = ./srcs/
SRC = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# BONUS
BNSDIR = ./bonus/
BNS = \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c

BNSOBJ = $(BNS:.c=.o)
BNSOBJS = $(addprefix $(OBJDIR), $(BNSOBJ))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# BONUS
bonus: $(BONUS)

$(BONUS): $(NAME) $(BNSOBJS)
	@ ar -rc $(BONUS) $(BNSOBJS)
	ar -rc $(NAME) $(BNSOBJS)
	ranlib $(NAME)

$(OBJDIR)%.o: $(BNSDIR)%.c $(INCS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

# MISC
clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
