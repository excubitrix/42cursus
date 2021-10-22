# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 08:00:57 by floogman          #+#    #+#              #
#    Updated: 2021/10/22 12:25:56 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft.a
LIBDIR = ./libft/

INC = ./includes/
SRCDIR = ./srcs/
SRC = \
	main.c \
	binexe.c \
	build_toklst_tools.c \
	build_toklst.c \
	check_syntax_tools.c \
	check_syntax.c \
	env_tools.c \
	execute.c \
	expand_line.c \
	expansion_tools.c \
	fd_tools.c \
	free_tools.c \
	ft_cd_env_pwd.c \
	ft_echo.c \
	ft_exit.c \
	ft_export_unset.c \
	get_cmd.c \
	get_cmdline.c \
	get_path.c \
	handlers.c \
	init.c \
	open_file.c \
	shlvl_tools.c \
	tools.c \
	tree_1.c \
	tree_2.c \
	tree_tools.c \
	term_ctrl.c \
	t_ft_atoi_array.c \
	t_utils.c \
	t_getters.c \
	t_history.c \
	t_initialise.c \
	t_line_manip.c \
	t_move_cursor_1.c \
	t_move_cursor_2.c \
	t_update_vars.c

OBJDIR = ./obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# BONUS
BONUS = srcs/bonus/bonus

BNSDIR = ./srcs/bonus/
BNS = \
	../main.c \
	../binexe.c \
	../build_toklst_tools.c \
	build_toklst_bonus.c \
	../check_syntax_tools.c \
	../check_syntax.c \
	../env_tools.c \
	../execute.c \
	../expand_line.c \
	../expansion_tools.c \
	../fd_tools.c \
	../free_tools.c \
	../ft_cd_env_pwd.c \
	../ft_echo.c \
	../ft_exit.c \
	../ft_export_unset.c \
	../get_cmd.c \
	../get_cmdline.c \
	../get_path.c \
	../handlers.c \
	../init.c \
	../open_file.c \
	../shlvl_tools.c \
	../tools.c \
	../tree_1.c \
	../tree_2.c \
	../tree_tools.c \
	../term_ctrl.c \
	../t_ft_atoi_array.c \
	../t_utils.c \
	../t_getters.c \
	../t_history.c \
	../t_initialise.c \
	../t_line_manip.c \
	../t_move_cursor_1.c \
	../t_move_cursor_2.c \
	../t_update_vars.c

BNSOBJDIR = ./obj/bonus/
BNSOBJ = $(BNS:.c=.o)
BNSOBJS = $(addprefix $(BNSOBJDIR), $(BNSOBJ))

RM = /bin/rm -f
RMDIR = /bin/rm -rf

# RULES *-------------------------------------------
all: $(NAME)
$(NAME): $(LIBDIR)$(LIBFT) $(OBJDIR) $(OBJS) $(INC)minishell.h
	@ echo "\n\033[0;32mCompiling minishell..."
	@ $(CC) $(CFLAGS) $(OBJS) -I$(INC) -L$(LIBDIR) -lft -ltermcap -o $(NAME)
	@ echo "Done!\033[0m"

# libft
$(LIBDIR)$(LIBFT):
	@ $(MAKE) -C $(LIBDIR)

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INC)minishell.h
	@ printf "\033[0;33mGenerating minishell %-33.33s\r" $@
	@ $(CC) $(CFLAGS) -I$(INC) -c -o $@ $<

# BONUS
bonus: $(BONUS)
$(BONUS): $(LIBDIR)$(LIBFT) $(BNSOBJDIR) $(BNSOBJS) $(INC)bonus.h
	@ echo "\n\033[0;32mCompiling bonus..."
	@ $(CC) $(CFLAGS) $(BNSOBJS) -I$(INC) -L$(LIBDIR) -lft -ltermcap -o $(BONUS)
	@ cp $(BONUS) ./$(NAME)
	@ echo "\033[0;32mDone!\033[0m"

$(BNSOBJDIR):
	@ mkdir -p $(BNSOBJDIR)

$(BNSOBJDIR)%.o: $(BNSDIR)%.c $(INC)bonus.h
	@ printf "\033[0;33mGenerating bonus %-33.33s\r" $@
	@ $(CC) $(CFLAGS) -I$(INC) -c -o $@ $<

# LEAKS
val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--log-file=valgrind-out.git-ign.txt \
	./$(NAME)

# MISC
clean:
	@ $(RM) $(OBJS) $(BNSOBJS)
	@ $(RMDIR) $(OBJDIR) $(BNSOBJDIR)

fclean: clean
	@ $(RM) $(NAME)
	@ $(RM) $(LIBDIR)$(LIBFT)

re: fclean all

re_bonus: fclean bonus

.PHONY: all lib bonus make_bonus val clean fclean re re_bonus
