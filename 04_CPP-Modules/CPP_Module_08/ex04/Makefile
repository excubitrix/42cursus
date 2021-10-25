NAME = ex04
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = \
	Calculator.cpp \
	Token.cpp \
	Close.cpp \
	Open.cpp \
	Num.cpp \
	Op.cpp \
	main.cpp 

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	Calculator.hpp \
	MutantStack.hpp \
	MutantStack.ipp \
	Token.hpp \
	Close.hpp \
	Open.hpp \
	Num.hpp \
	Op.hpp

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
