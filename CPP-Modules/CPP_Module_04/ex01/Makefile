NAME = a.out
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic-errors

SRCS = \
	AWeapon.cpp \
	Character.cpp \
	Dragon.cpp \
	Enemy.cpp \
	Mongrel.cpp \
	PlasmaRifle.cpp \
	PowerFist.cpp \
	RadScorpion.cpp \
	RocketLauncher.cpp \
	SuperMutant.cpp \
	Whip.cpp \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	AWeapon.hpp \
	Character.hpp \
	Dragon.hpp \
	Enemy.hpp \
	Mongrel.hpp \
	PlasmaRifle.hpp \
	PowerFist.hpp \
	RadScorpion.hpp \
	RocketLauncher.hpp \
	SuperMutant.hpp \
	Whip.hpp

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
