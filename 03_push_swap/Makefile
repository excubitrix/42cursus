NAME1 = push_swap
NAME2 = checker

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I $(INCDIR) -c
LIBS = -L$(LIBDIR) -lft

LIBDIR = ./libft/
LIBFT = $(LIBDIR)libft.a

SRCDIR = ./srcs/
SRC1 = \
	free_all.c \
	init.c \
	ops_a.c \
	ops_b.c \
	ops.c \
	push_swap.c \
	push_tools.c \
	tools.c

SRC2 = \
	checker.c \
	free_all.c \
	init.c \
	ops_a.c \
	ops_b.c \
	ops.c \
	push_tools.c \
	tools.c

FILLER = $(OBJDIR)dummies.o

OBJDIR = ./obj/
OBJ1 = $(SRC1:.c=.o)
OBJS1 = $(addprefix $(OBJDIR), $(OBJ1))
OBJ2 = $(SRC2:.c=.o)
OBJS2 = $(addprefix $(OBJDIR), $(OBJ2))

INCDIR = ./includes/
INC = push_swap.h
INCS = $(addprefix $(INCDIR), $(INC))

#BONUS
BONUS1 = $(SRCDIR)bonus/push_swap_bonus
BONUS2 = $(SRCDIR)bonus/checker_bonus

BONUS = \
	$(OBJDIR)bonus.o \
	$(OBJDIR)print.o

# RULES *-------------------------------------------
all: $(NAME1) $(NAME2)
$(NAME1): $(LIBFT) $(OBJDIR) $(OBJS1) $(FILLER) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME1) ..."
	@ $(CC) $(CFLAGS) $(OBJS1) $(FILLER) $(LIBS) -o $(NAME1)
	@ echo "Done!\033[0m"

$(NAME2): $(LIBFT) $(OBJDIR) $(OBJS2) $(FILLER) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME2) ..."
	@ $(CC) $(CFLAGS) $(OBJS2) $(FILLER) $(LIBS) -o $(NAME2)
	@ echo "Done!\033[0m"

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@ printf "\033[0;33mGenerating object file %-33.33s\r" $@
	@ $(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# LIBFT
$(LIBFT):
	@ $(MAKE) -C $(LIBDIR)

# BONUS
bonus: $(BONUS1) $(BONUS2)
$(BONUS1): $(LIBFT) $(OBJDIR) $(OBJS1) $(BONUS) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME1) ..."
	@ $(CC) $(CFLAGS) $(OBJS1) $(BONUS) $(LIBS) -o $(BONUS1)
	@ cp $(BONUS1) $(NAME1)
	@ echo "Done!\033[0m"

$(BONUS2): $(LIBFT) $(OBJDIR) $(OBJS2) $(BONUS) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME2) ..."
	@ $(CC) $(CFLAGS) $(OBJS2) $(BONUS) $(LIBS) -o $(BONUS2)
	@ cp $(BONUS2) $(NAME2)
	@ echo "Done!\033[0m"

$(OBJDIR)%.o: $(SRCDIR)bonus/%.c $(INCS)
	@ printf "\033[0;33mGenerating object file %-33.33s\r" $@
	@ $(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

# MISC
clean:
	@ rm -rf $(OBJDIR)
	@ $(MAKE) clean -C $(LIBDIR)

fclean: clean
	@ rm -f $(NAME1) $(NAME2) $(LIBFT)
	@ $(MAKE) fclean -C $(LIBDIR)

re: fclean all

.PHONY: all bonus clean fclean re
