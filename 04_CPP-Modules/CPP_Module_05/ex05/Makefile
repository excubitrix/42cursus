NAME = ex05
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = \
	Bureaucrat.cpp \
	CentralBureaucracy.cpp \
	Form.cpp \
	Intern.cpp \
	MutantPigTerminationForm.cpp \
	OfficeBlock.cpp \
	PresidentialPardonForm.cpp \
	RobotomyRequestForm.cpp \
	ShrubberyCreationForm.cpp \
	main.cpp

OBJDIR = ./obj/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

INCS = \
	Bureaucrat.hpp \
	CentralBureaucracy.hpp \
	Form.hpp \
	Intern.hpp \
	MutantPigTerminationForm.hpp \
	OfficeBlock.hpp \
	PresidentialPardonForm.hpp \
	RobotomyRequestForm.hpp \
	ShrubberyCreationForm.hpp

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
