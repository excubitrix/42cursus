OUT = 00.out
NAME = traps
DIR = ./ex00/

OUT1 = 01.out
NAME1 = traps
DIR1 = ./ex01/

OUT2 = 02.out
NAME2 = traps
DIR2 = ./ex02/

OUT3 = 03.out
NAME3 = traps
DIR3 = ./ex03/

OUT4 = 04.out
NAME4 = traps
DIR4 = ./ex04/

# RULES *-------------------------------------------
all: $(OUT) $(OUT1) $(OUT2) $(OUT3) $(OUT4)

$(OUT):
	@ $(MAKE) -C $(DIR)
	cp $(DIR)$(NAME) $(OUT)

$(OUT1):
	@ $(MAKE) -C $(DIR1)
	cp $(DIR1)$(NAME1) $(OUT1)

$(OUT2):
	@ $(MAKE) -C $(DIR2)
	cp $(DIR2)$(NAME2) $(OUT2)

$(OUT3):
	@ $(MAKE) -C $(DIR3)
	cp $(DIR3)$(NAME3) $(OUT3)

$(OUT4):
	@ $(MAKE) -C $(DIR4)
	cp $(DIR4)$(NAME4) $(OUT4)

# MISC
clean:
	@ $(MAKE) clean -C $(DIR)
	@ $(MAKE) clean -C $(DIR1)
	@ $(MAKE) clean -C $(DIR2)
	@ $(MAKE) clean -C $(DIR3)
	@ $(MAKE) clean -C $(DIR4)

fclean: clean
	@ rm -f $(OUT) $(OUT1) $(OUT2) $(OUT3) $(OUT4)
	@ $(MAKE) fclean -C $(DIR)
	@ $(MAKE) fclean -C $(DIR1)
	@ $(MAKE) fclean -C $(DIR2)
	@ $(MAKE) fclean -C $(DIR3)
	@ $(MAKE) fclean -C $(DIR4)

re: fclean all

.PHONY: all clean fclean re
