NAME1 = push_swap
NAME2 = checker

LIBDIR = ./libft/
LIBFT = $(LIBDIR)libft.a

INCDIR = ./includes/
INCS = $(INCDIR)push_swap.h

SRCDIR = ./srcs/
OBJDIR = ./obj/

BONUS1 = $(SRCDIR)bonus/push_swap_bonus
BONUS2 = $(SRCDIR)bonus/checker_bonus

# PUSH_SWAP
SRC1 = \
	push_swap.c \
	free_all.c \
	init.c \
	ops_a.c \
	ops_b.c \
	ops.c \
	push_tools.c \
	tools.c

OBJ1 = $(SRC1:.c=.o)
OBJS1 = $(addprefix $(OBJDIR), $(OBJ1))

# CHECKER
SRC2 = \
	checker.c \
	free_all.c \
	init.c \
	ops_a.c \
	ops_b.c \
	ops.c \
	push_tools.c \
	tools.c

OBJ2 = $(SRC2:.c=.o)
OBJS2 = $(addprefix $(OBJDIR), $(OBJ2))

FILLER = $(OBJDIR)dummies.o
BONUS = \
	$(OBJDIR)bonus.o \
	$(OBJDIR)print.o

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -f
RMDIR = /bin/rm -rf

# RULES *-------------------------------------------
all: $(NAME1) $(NAME2)
$(NAME1): $(LIBFT) $(OBJDIR) $(OBJS1) $(FILLER) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME1) ..."
	@ $(CC) $(CFLAGS) $(OBJS1) $(FILLER) -I$(INCDIR) -L$(LIBDIR) -lft -o $(NAME1)
	@ echo "Done!\033[0m"

$(NAME2): $(LIBFT) $(OBJDIR) $(OBJS2) $(FILLER) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME2) ..."
	@ $(CC) $(CFLAGS) $(OBJS2) $(FILLER) -I$(INCDIR) -L$(LIBDIR) -lft -o $(NAME2)
	@ echo "Done!\033[0m"

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@ printf "\033[0;33mGenerating object file %-33.33s\r" $@
	@ $(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

# BONUS
bonus: $(BONUS1) $(BONUS2)
$(BONUS1): $(LIBFT) $(OBJDIR) $(OBJS1) $(BONUS) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME1) ..."
	@ $(CC) $(CFLAGS) $(OBJS1) $(BONUS) -I$(INCDIR) -L$(LIBDIR) -lft -o $(BONUS1)
	@ cp $(BONUS1) $(NAME1)
	@ echo "Done!\033[0m"

$(BONUS2): $(LIBFT) $(OBJDIR) $(OBJS2) $(BONUS) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME2) ..."
	@ $(CC) $(CFLAGS) $(OBJS2) $(BONUS) -I$(INCDIR) -L$(LIBDIR) -lft -o $(BONUS2)
	@ cp $(BONUS2) $(NAME2)
	@ echo "Done!\033[0m"

$(OBJDIR)%.o: $(SRCDIR)bonus/%.c $(INCS)
	@ printf "\033[0;33mGenerating object file %-33.33s\r" $@
	@ $(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

# libft
$(LIBFT):
	@ $(MAKE) -C $(LIBDIR)

# MISC
clean:
	@ $(RM) $(OBJS1) $(OBJS2)
	@ $(RMDIR) $(OBJDIR)
	@ $(MAKE) clean -C $(LIBDIR)

fclean: clean
	@ $(RM) $(NAME1) $(NAME2)
	@ $(RM) $(LIBFT)

re: fclean all

.PHONY: all bonus clean fclean re
