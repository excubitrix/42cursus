OUT = 00.out
NAME = ponies
DIR = ./ex00/

OUT2 = 02.out
NAME2 = zombies
DIR2 = ./ex02/

OUT3 = 03.out
NAME3 = horde
DIR3 = ./ex03/

OUT4 = 04.out
NAME4 = ex04
DIR4 = ./ex04/

OUT5 = 05.out
NAME5 = brainz
DIR5 = ./ex05/

OUT6 = 06.out
NAME6 = clubs
DIR6 = ./ex06/

OUT7 = 07.out
NAME7 = replace
DIR7 = ./ex07/

OUT8 = 08.out
NAME8 = attack
DIR8 = ./ex08/

OUT9 = 09.out
NAME9 = logger
DIR9 = ./ex09/

OUT10 = 10.out
NAME10 = cato9tails
DIR10 = ./ex10/

# RULES *-------------------------------------------
all: $(OUT) $(OUT2) $(OUT3) $(OUT4) $(OUT5) $(OUT6) $(OUT7) $(OUT8) $(OUT9) $(OUT10)

$(OUT):
	@ $(MAKE) -C $(DIR)
	cp $(DIR)$(NAME) $(OUT)

$(OUT2):
	@ $(MAKE) -C $(DIR2)
	cp $(DIR2)$(NAME2) $(OUT2)

$(OUT3):
	@ $(MAKE) -C $(DIR3)
	cp $(DIR3)$(NAME3) $(OUT3)

$(OUT4):
	@ $(MAKE) -C $(DIR4)
	cp $(DIR4)$(NAME4) $(OUT4)

$(OUT5):
	@ $(MAKE) -C $(DIR5)
	cp $(DIR5)$(NAME5) $(OUT5)

$(OUT6):
	@ $(MAKE) -C $(DIR6)
	cp $(DIR6)$(NAME6) $(OUT6)

$(OUT7):
	@ $(MAKE) -C $(DIR7)
	cp $(DIR7)$(NAME7) $(OUT7)

$(OUT8):
	@ $(MAKE) -C $(DIR8)
	cp $(DIR8)$(NAME8) $(OUT8)

$(OUT9):
	@ $(MAKE) -C $(DIR9)
	cp $(DIR9)$(NAME9) $(OUT9)

$(OUT10):
	@ $(MAKE) -C $(DIR10)
	cp $(DIR10)$(NAME10) $(OUT10)

# MISC
clean:
	@ $(MAKE) clean -C $(DIR)
	@ $(MAKE) clean -C $(DIR2)
	@ $(MAKE) clean -C $(DIR3)
	@ $(MAKE) clean -C $(DIR4)
	@ $(MAKE) clean -C $(DIR5)
	@ $(MAKE) clean -C $(DIR6)
	@ $(MAKE) clean -C $(DIR7)
	@ $(MAKE) clean -C $(DIR8)
	@ $(MAKE) clean -C $(DIR9)
	@ $(MAKE) clean -C $(DIR10)

fclean: clean
	@ rm -f $(OUT) $(OUT2) $(OUT3) $(OUT4) $(OUT5) $(OUT6) $(OUT7) $(OUT8) $(OUT9) $(OUT10)
	@ $(MAKE) fclean -C $(DIR)
	@ $(MAKE) fclean -C $(DIR2)
	@ $(MAKE) fclean -C $(DIR3)
	@ $(MAKE) fclean -C $(DIR4)
	@ $(MAKE) fclean -C $(DIR5)
	@ $(MAKE) fclean -C $(DIR6)
	@ $(MAKE) fclean -C $(DIR7)
	@ $(MAKE) fclean -C $(DIR8)
	@ $(MAKE) fclean -C $(DIR9)
	@ $(MAKE) fclean -C $(DIR10)

re: fclean all

.PHONY: all clean fclean re
