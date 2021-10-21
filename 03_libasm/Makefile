# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/27 16:04:31 by floogman          #+#    #+#              #
#    Updated: 2021/10/13 12:13:06 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

NASM = /usr/bin/nasm
# NASM = /usr/local/bin/nasm
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

# MISC
clean:
	@ /bin/rm -rf $(OBJDIR)

fclean: clean
	@ /bin/rm -f $(NAME)
	
re: fclean all

.PHONY: all bonus clean fclean re
