ONE = philo_one
ONEDIR = ./philo_one

TWO = philo_two
TWODIR = ./philo_two

THREE = philo_three
THREEDIR = ./philo_three

# RULES *-------------------------------------------
all: $(ONE) $(TWO) $(THREE)

$(ONE):
	@ $(MAKE) -C $(ONEDIR)
	cp $(ONEDIR)$(ONE) .

$(TWO):
	@ $(MAKE) -C $(TWODIR)
	cp $(TWODIR)$(TWO) .

$(THREE):
	@ $(MAKE) -C $(THREEDIR)
	cp $(THREEDIR)$(THREE) .

# MISC
clean:
	@ $(MAKE) clean -C $(ONEDIR)
	@ $(MAKE) clean -C $(TWODIR)
	@ $(MAKE) clean -C $(THREEDIR)

fclean: clean
	@ /bin/rm -f $(ONE) $(TWO) $(THREE)
	@ $(MAKE) fclean -C $(ONEDIR)
	@ $(MAKE) fclean -C $(TWODIR)
	@ $(MAKE) fclean -C $(THREEDIR)

re: fclean all

.PHONY: all clean fclean re
