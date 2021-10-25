OUT = 00.out
NAME = ex00
DIR = ./ex00/

OUT1 = 01.out
NAME1 = ex01
DIR1 = ./ex01/

OUT2 = 02.out
NAME2 = ex02
DIR2 = ./ex02/

# RULES *-------------------------------------------
all: $(OUT) $(OUT1) $(OUT2)

$(OUT):
	@ $(MAKE) -C $(DIR)
	cp $(DIR)$(NAME) $(OUT)

$(OUT1):
	@ $(MAKE) -C $(DIR1)
	cp $(DIR1)$(NAME1) $(OUT1)

$(OUT2):
	@ $(MAKE) -C $(DIR2)
	cp $(DIR2)$(NAME2) $(OUT2)

# MISC
clean:
	@ $(MAKE) clean -C $(DIR)
	@ $(MAKE) clean -C $(DIR1)
	@ $(MAKE) clean -C $(DIR2)

fclean: clean
	@ rm -f $(OUT) $(OUT1) $(OUT2)
	@ $(MAKE) fclean -C $(DIR)
	@ $(MAKE) fclean -C $(DIR1)
	@ $(MAKE) fclean -C $(DIR2)

re: fclean all

.PHONY: all clean fclean re
