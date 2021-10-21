NAME = traps
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic-errors

SRCS = \
	ClapTrap.cpp \
	FragTrap.cpp \
	NinjaTrap.cpp \
	ScavTrap.cpp \
	SuperTrap.cpp \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	ClapTrap.hpp \
	FragTrap.hpp \
	NinjaTrap.hpp \
	SuperTrap.hpp \
	ScavTrap.hpp

all: $(NAME)
$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	@ clang++ $(FLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o:%.cpp $(INCS)
	@ clang++ $(FLAGS) -c -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# MISC
clean:
	@ /bin/rm -rf $(OBJDIR)

fclean: clean
	@ /bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
