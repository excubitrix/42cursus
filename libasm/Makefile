# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/27 16:04:31 by floogman          #+#    #+#              #
#    Updated: 2021/10/07 13:13:23 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

NASM = /usr/local/bin/nasm
NASM_FLAGS = -f macho64

SRCDIR = ./srcs/
SRC = \
	ft_read.s \
	ft_strcmp.s \
	ft_strcpy.s \
	ft_strdup.s \
	ft_strlen.s \
	ft_write.s

OBJDIR = ./obj/
OBJ = $(SRC:.s=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./includes/
INC = libasm.h
INCS = $(addprefix $(INCDIR), $(INC))

# BONUS
BONUS = $(BNSDIR)bonus.a

BNSDIR = ./bonus/
BNS = \
	ft_atoi_base.s \
	ft_list_push_front.s \
	ft_list_remove_if.s \
	ft_list_size.s \
	ft_list_sort.s

BNSOBJ = $(BNS:.s=.o)
BNSOBJS = $(addprefix $(OBJDIR), $(BNSOBJ))

BNSINC = bonus.h
BNSINCS = $(addprefix $(BNSDIR), $(BNSINC))

# RULES *-------------------------------------------
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	@ ar rc $(NAME) $(OBJS)
	@ ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.s
	@ $(NASM) $(NASM_FLAGS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# BONUS
bonus: $(BONUS)

$(BONUS): $(OBJDIR) $(OBJS) $(BNSOBJS) $(INCS) $(BNSINCS)
	@ ar rc $(NAME) $(OBJS) $(BNSOBJS)
	@ ranlib $(NAME)

$(OBJDIR)%.o: $(BNSDIR)%.s
	@ $(NASM) $(NASM_FLAGS) -o $@ $<

# make test (mandatory functions) -------------------------
TEST = out
TEST_SRC = \
	./testing/main.c \
	./testing/tests.c \
	./testing/tools.c

INC = ./testing/

test: $(TEST)
$(TEST): $(NAME) $(TEST_SRC)
	@ gcc -Wall -Wextra -Werror -I$(INC) -L. -lasm -o $(TEST) $(TEST_SRC)

# BONUS
TEST_BONUS = out_bonus
BONUS_SRC = \
	./testing/main_bonus.c \
	./testing/tests_bonus.c \
	./testing/ft_atoi_base_c.c \
	./testing/tools.c

test_bonus: $(TEST_BONUS)
$(TEST_BONUS): bonus $(TEST_BONUS_SRC)
	@ gcc -Wall -Wextra -Werror -I$(INC) -L. -lasm -o $(TEST_BONUS) $(BONUS_SRC)

# MISC
clean:
	@ /bin/rm -rf $(OBJDIR)

fclean: clean
	@ /bin/rm -f $(NAME)
	
re: fclean all

.PHONY: all bonus clean fclean re
