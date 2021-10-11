NAME = a.out
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic-errors

SRCS = \
	MindOpen.cpp \
	Decrement.cpp \
	Increment.cpp \
	LoopEnd.cpp \
	LoopStart.cpp \
	MoveLeft.cpp \
	MoveRight.cpp \
	Read.cpp \
	Write.cpp \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	MindOpen.hpp \
	IInstruction.hpp \
	Decrement.hpp \
	Increment.hpp \
	LoopEnd.hpp \
	LoopStart.hpp \
	MoveLeft.hpp \
	MoveRight.hpp \
	Read.hpp \
	Write.hpp

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
