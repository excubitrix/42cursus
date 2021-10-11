NAME = a.out
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic-errors

SRCS = \
	Account.class.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCDIR = ./resources/
TEST_FILE = $(INCDIR)tests.cpp

all: $(NAME)
$(NAME): $(OBJDIR) $(OBJS) $(INCDIR)Account.class.hpp
	@ clang++ $(FLAGS) $(OBJS) $(TEST_FILE) -I$(INCDIR) -o $(NAME)

$(OBJDIR)%.o:%.cpp $(INCDIR)Account.class.hpp
	@ clang++ $(FLAGS) -I$(INCDIR) -c -o $@ $<

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# MISC
clean:
	@ /bin/rm -rf $(OBJDIR)

fclean: clean
	@ /bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
