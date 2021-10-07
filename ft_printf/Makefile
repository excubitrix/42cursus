# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/10/07 13:09:18 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I$(INCDIR) -c

LIBDIR = ../Libft/
LIBFT = libft.a

SRCDIR = ./srcs/
SRC = \
	conv_e.c \
	conv_f.c \
	conv_png.c \
	utils.c

SHRD = \
	conv_cs.c \
	conv_di.c \
	conv_ux.c \
	conv_ws.c \
	display_wchar.c \
	ft_itoa_base.c \
	ft_printf.c \
	ft_strndup.c \
	get.c \
	padding.c \
	tab.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o) $(SHRD:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./includes/
INC = ft_printf.h
INCS = $(addprefix $(INCDIR), $(INC))

# BONUS
BONUS = libbnsprintf.a

BNSDIR = ./srcs/
BNS = \
	conv_e_bonus.c \
	conv_f_bonus.c \
	conv_png_bonus.c \
	utils_bonus.c

BNSOBJ = $(BNS:.c=.o) $(SHRD:.c=.o)
BNSOBJS = $(addprefix $(OBJDIR), $(BNSOBJ))

BNSINC = ft_printf_bonus.h
BNSINCS = $(addprefix $(INCDIR), $(BNSINC))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS) $(INCS)
	cp $(LIBFT) $(NAME)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# LIBFT
$(LIBFT): $(LIBDIR)$(LIBFT)
	cp $(LIBDIR)$(LIBFT) .

$(LIBDIR)$(LIBFT):
	$(MAKE) -C $(LIBDIR)

# BONUS
bonus: $(BONUS)

$(BONUS): $(LIBFT) $(OBJDIR) $(BNSOBJS) $(BNSINCS)
	cp $(LIBFT) $(BONUS)
	ar -rc $(BONUS) $(BNSOBJS)
	ranlib $(BONUS)
	cp $(BONUS) $(NAME)

$(OBJDIR)%.o: $(BNSDIR)%.c $(BNSINCS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

# DEBUG
debug:
	$(CC) $(CFLAGS) -g -I./debugging ./debugging/*.c

# MISC
clean:
	$(MAKE) -C $(LIBDIR) clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	/bin/rm -f $(NAME) $(BONUS) $(LIBFT)

re: fclean all

.PHONY: all test bonus clean fclean re
