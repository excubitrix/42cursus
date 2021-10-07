# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/10/07 13:10:20 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# BUFFER_SIZE *-------------------------------------
VAR = -D BUFFER_SIZE=32
# *-------------------------------------------------
OPTIONS = $(VAR) -c

SRCDIR = ./
SRC = \
	get_next_line.c \
	get_next_line_utils.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INC = get_next_line.h
INCS = $(addprefix $(SRCDIR), $(INC))

# BONUS
BONUS = $(BNSDIR)libbns.a

BNSDIR = ./bonus/
BNS = \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c

BNSOBJ = $(BNS:.c=.o)
BNSOBJS = $(addprefix $(OBJDIR), $(BNSOBJ))

BNSINC = get_next_line_bonus.h
BNSINCS = $(addprefix $(BNSDIR), $(BNSINC))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	$(CC) $(CFLAGS) -I$(SRCDIR) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# BONUS
bonus: $(BONUS)

$(BONUS): $(OBJDIR) $(BNSOBJS) $(BNSINCS)
	ar -rc $(BONUS) $(BNSOBJS)
	ranlib $(BONUS)
	cp $(BONUS) $(NAME)

$(OBJDIR)%.o: $(BNSDIR)%.c $(BNSINCS)
	$(CC) $(CFLAGS) -I$(BNSDIR) $(OPTIONS) -o $@ $<

# MISC
clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
