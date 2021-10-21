NAME1 = one
ONE = philo_one
ONEDIR = ./philo_one/

NAME2 = two
TWO = philo_two
TWODIR = ./philo_two/

NAME3 = three
THREE = philo_three
THREEDIR = ./philo_three/

# RULES *-------------------------------------------
all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1):
	@ $(MAKE) -C $(ONEDIR)
	cp $(ONEDIR)$(ONE) $(NAME1)

$(NAME2):
	@ $(MAKE) -C $(TWODIR)
	cp $(TWODIR)$(TWO) $(NAME2)

$(NAME3):
	@ $(MAKE) -C $(THREEDIR)
	cp $(THREEDIR)$(THREE) $(NAME3)

# MISC
clean:
	@ $(MAKE) clean -C $(ONEDIR)
	@ $(MAKE) clean -C $(TWODIR)
	@ $(MAKE) clean -C $(THREEDIR)

fclean: clean
	@ rm -f $(NAME1) $(NAME2) $(NAME3)
	@ $(MAKE) fclean -C $(ONEDIR)
	@ $(MAKE) fclean -C $(TWODIR)
	@ $(MAKE) fclean -C $(THREEDIR)

re: fclean all

.PHONY: all clean fclean re
