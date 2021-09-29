# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 08:31:53 by floogman          #+#    #+#              #
#    Updated: 2021/09/28 13:55:33 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.out
BONUS = gnl_bonus.out
FLAGS = -Wall -Wextra -Werror

# BUFFER_SIZE *-------------------------------------
VAR = -D BUFFER_SIZE=42
# *-------------------------------------------------

INCDIR = ./includes/
INC = get_next_line.h
INCS = $(addprefix $(INCDIR), $(INC))

SRCDIR = ./srcs/
SRC = \
	main.c \
	get_next_line.c \
	get_next_line_utils.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# BONUS
BNSINC = get_next_line_bonus.h
BNSINCS = $(addprefix $(INCDIR), $(BNSINC))

BNSDIR = ./bonus/
BNS = \
	main_bonus.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c

BNSOBJ = $(BNS:.c=.o)
BNSOBJS = $(addprefix $(OBJDIR), $(BNSOBJ))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	gcc $(FLAGS) $(OBJS) -I$(INCDIR) $(VAR) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	gcc $(FLAGS) -I$(INCDIR) $(VAR) -c -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# BONUS
bonus: $(BONUS)

$(BONUS): $(OBJDIR) $(BNSOBJS) $(BNSINCS)
	gcc $(FLAGS) $(BNSOBJS) -I$(INCDIR) $(VAR) -o $(BONUS)

$(OBJDIR)%.o: $(BNSDIR)%.c $(BNSINCS)
	gcc $(FLAGS) -I$(INCDIR) $(VAR) -c -o $@ $<

# MISC
clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
