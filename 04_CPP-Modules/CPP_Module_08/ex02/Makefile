NAME = ex02
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	MutantStack.ipp \
	MutantStack.hpp

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
