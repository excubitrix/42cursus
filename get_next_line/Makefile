# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/09/29 13:44:50 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
BONUS = $(BNSDIR)libbns.a
FLAGS = -Wall -Wextra -Werror

# BUFFER_SIZE *-------------------------------------
VAR = -D BUFFER_SIZE=32
# *-------------------------------------------------

INC = get_next_line.h
INCS = $(addprefix $(SRCDIR), $(INC))

SRCDIR = ./
SRC = \
	get_next_line.c \
	get_next_line_utils.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# BONUS
BNSINC = get_next_line_bonus.h
BNSINCS = $(addprefix $(BNSDIR), $(BNSINC))

BNSDIR = ./bonus/
BNS = \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c

BNSOBJ = $(BNS:.c=.o)
BNSOBJS = $(addprefix $(OBJDIR), $(BNSOBJ))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	gcc $(FLAGS) $(VAR) -I $(SRCDIR) -c -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# BONUS
bonus: $(BONUS)

$(BONUS): $(OBJDIR) $(BNSOBJS) $(BNSINCS)
	ar -rc $(BONUS) $(BNSOBJS)
	ranlib $(BONUS)
	cp $(BONUS) $(NAME)

$(OBJDIR)%.o: $(BNSDIR)%.c $(BNSINCS)
	gcc $(FLAGS) $(VAR) -I $(BNSDIR) -c -o $@ $<

# MISC
clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
