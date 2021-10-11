NAME = a.out
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic-errors

SRCS = \
	Asteroid.cpp \
	Comet.cpp \
	DeepCoreMiner.cpp \
	MiningBarge.cpp \
	StripMiner.cpp \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	Asteroid.hpp \
	Comet.hpp \
	DeepCoreMiner.hpp \
	MiningBarge.hpp \
	IAsteroid.hpp \
	IMiningLaser.hpp \
	StripMiner.hpp

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
