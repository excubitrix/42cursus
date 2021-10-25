NAME = ex00
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = \
	Boy.cpp \
	Sorcerer.cpp \
	Victim.cpp \
	Peon.cpp \
	Princess.cpp \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	Boy.hpp \
	Sorcerer.hpp \
	Victim.hpp \
	Peon.hpp \
	Princess.hpp

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
