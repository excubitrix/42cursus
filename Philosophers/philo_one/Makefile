NAME = philo_one

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I $(INCDIR) -c

SRCDIR = ./srcs/
SRC = \
	init.c \
	main.c \
	philo.c \
	utils.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./includes/
INC = philo_one.h
INCS = $(addprefix $(INCDIR), $(INC))

# RULES *-------------------------------------------
all: $(NAME)
$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	@ echo "\n\033[0;32mCompiling $(NAME) ..."
	@ $(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@ echo "Done!\033[0m"

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@ printf "\033[0;33mGenerating object file %-33.33s\r" $@
	@ $(CC) $(CFLAGS) $(OPTIONS) -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# MISC
clean:
	@ /bin/rm -rf $(OBJDIR)

fclean: clean
	@ /bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
