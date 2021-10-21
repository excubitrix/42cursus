/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:33:11 by floogman          #+#    #+#             */
/*   Updated: 2021/03/26 18:54:04 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>

# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERR 2
# define DIRECTORY 126
# define NOT_FOUND 127

# define STDIN	0
# define STDOUT	1
# define STDERR	2
# define BUFSIZE 999
# define FDCAP	10495

# define PIPE 0
# define REDIRECT_IN 1
# define REDIRECT_FD_IN 2
# define REDIRECT_OUT 3
# define REDIRECT_FD_OUT 4
# define REDIRECT_APPEND 5
# define REDIRECT_FD_APPEND 6
# define CMDPATH 7
# define ARGUMENT 8

# define KEY_ESC 27
# define KEY_RETURN 10
# define KEY_BCKSPACE 127
# define KEY_CTRL_C 3
# define KEY_CTRL_D 4
# define KEY_CTRL_BACKSLASH 28
# define KEY_CTRL_U 21
# define KEY_ARROW_L 1
# define KEY_ARROW_R 5

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define REVERSED "\033[7m"

typedef struct		s_tok
{
	char			*data;
	int				type;
	int				digit;
	int				space;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_node
{
	int				type;
	int				fd;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct		s_cmd
{
	int				argc;
	char			**argv;
}					t_cmd;

typedef struct		s_term
{
	struct termios	original_termios;
	int				initialised;
	int				put_prompt;
	int				prompt_len;
	char			*prompt;
	char			*line;
	char			**history;
	int				history_index;
	int				history_len;
	int				scrn_rows;
	int				scrn_cols;
	int				cursor_y_start;
	int				cursor_x;
	int				cursor_y;
	int				index;
	int				index_row;
	int				n_rows_line;
	int				fd;
	char			*line_save;
	char			*tc_cursor_move;
	char			*tc_cursor_move_to_col;
	char			*tc_remove_all_after_cursor;
	char			*tc_cursor_invisible;
	char			*tc_cursor_visible;
	char			*tc_store_cursor_position;
	char			*tc_restore_cursor_position;
}					t_term;

typedef struct		s_info
{
	int				in;
	int				out;
	char			**envp;
	char			*path;
	char			*home;
	char			*line;
	char			*cmd;
	int				size;
	t_tok			*toklst;
	t_tok			*pretok;
	t_tok			*curtok;
	t_tok			*nextok;
	t_node			*tree;
	int				charge;
	int				parent;
	int				last;
	int				fd;
	int				fd_in;
	int				fd_out;
	int				pipe_in;
	int				pipe_out;
	char			**cmdstr;
	int				(**cmdexe)(struct s_info *, t_cmd *);
	int				error;
	int				and;
	int				or;
	int				ret;
	t_term			*trm_ptr;
}					t_info;

typedef struct		s_sig
{
	int				sigint;
	int				sigquit;
	pid_t			pid;
	int				exstat;
}					t_sig;

extern t_sig		g_sig;

/*
** binexe
*/
int					launch(t_info *info, t_cmd *cmd, char *path, char **args);
char				*check_dir(char *bin, char *cmd);
void				set__(t_info *info, t_cmd *cmd, char *path);
int					binexe(t_info *info, t_cmd *cmd, char **bin, char *value);

/*
** build toklst tools
*/
void				copy_data(t_tok *tok, char **cmd, int *quote, int *j);
void				type_tok(t_info *info, char **cmd);
void				next_tok(t_info *info, char **cmd, int *j);
int					check_more_cases(t_info *info, char **cmd, int *j);
int					check_cases(t_info *info, char **cmd, int *quote, int *j);

/*
** build toklst
*/
void				get_toks(t_info *info, char **cmd);
void				build_toklst(t_info *info, char *cmd);

/*
** check syntax tools
*/
int					set_and_return(int *ptr, int var, int ret);
int					is_special(int c);
int					check_general(int *first, int *quote, int *i, int c);

/*
** check syntax
*/
int					check_redir(char *cmd, int *first, int *i, int c);
int					check_special(char *cmd, int *first, int *i, int c);
int					check_syntax(char *cmd, int first, int quote, int i);

/*
** execute
*/
int					add_envar(t_info *info, char *arg);
int					set_envar(t_info *info, char *arg, char *ptr, int append);
int					get_envp(t_info *info, char *needle);

/*
** execute
*/
int					prep_cmd(t_info *info, t_cmd *cmd, t_node *job,
						t_node *arg);
void				execute_cmd(t_info *info, t_node *job);
int					pipe_cmd(t_info *info, pid_t pid, int *fd);
void				redirect_cmd(t_info *info, t_node **cmd);
void				execute(t_info *info, t_node *tree, int prev);

/*
** expand line
*/
char				*envar_expansion(t_info *info, char *line, int *i);
char				*last_exstat_expansion(t_info *info, char *line, int *i,
						char next);
char				*tilde_expansion(t_info *info, char *line, int *i);
char				*expand_line(t_info *info, char *line, int i, int quote);

/*
** expansion tools
*/
int					is_sep(int c);
int					get_key(char *s, int i, char **key);
char				*get_value(t_info *info, char *key);
char				*check_users(t_info *info, char *s, int len);

/*
** fd tools
*/
void				ft_close(int fd);
void				restore_std(t_info *info);
void				close_fds(t_info *info);
void				reset_fds(t_info *info);

/*
** free tools
*/
void				free_toks(t_tok *tok);
void				clear_toklst(t_info *info);
void				clear_tree(t_info *info);
void				clear_cmd(t_cmd *cmd);
void				free_all(t_info *info, t_cmd *cmd, int i);

/*
** cd | env | pwd
*/
int					ft_cd(t_info *info, t_cmd *cmd);
int					ft_env(t_info *info, t_cmd *cmd);
int					ft_pwd(t_info *info, t_cmd *cmd);

/*
** echo
*/
int					ft_echo(t_info *info, t_cmd *cmd);

/*
** exit
*/
int					ft_exit(t_info *info, t_cmd *cmd);

/*
** export | unset
*/
int					ft_export(t_info *info, t_cmd *cmd);
int					ft_unset(t_info *info, t_cmd *cmd);

/*
** get cmd
*/
int					set_and_or(t_info *info, char *ptr, int *i);
char				*get_cmd(t_info *info, char *ptr, char *tmp, char *cmd);

/*
** get cmdline
*/
int					get_line(char **line, int bytes);
void				get_cmdline(t_info *info, int not_pipe);

/*
** get path
*/
void				set_prompt(t_info *info);
int					get_path(t_info *info, t_cmd *cmd);

/*
** handlers
*/
void				ctrl_d(t_info *info);
void				sig_handler(int signum);

/*
** init
*/
void				init_sig(void);
void				init_cmdstr(t_info *info);
void				init_cmdexe(t_info *info);
int					init_info(t_info *info, char **envp);
t_tok				*init_tok(t_tok *tok, int size);

/*
** main
*/
void				parse_and_exec(t_info *info, int skip);
void				minishell(t_info *info, int not_pipe, int i);

/*
** open file
*/
int					open_file_in(t_info *info, char *file);
int					open_file_out(t_info *info, char *file, int append);

/*
** shlvl tools
*/
void				increment_num(t_info *info, int j, int key_len,
						int val_len);
void				increment_len(t_info *info, int j, int key_len);
int					reset_shlvl(t_info *info, int j, int key_len);
void				increment_shlvl(t_info *info, int j, int key_len);

/*
** t_ft_atoi_array.c
*/
int					*ft_atoi_array(char *s);

/*
** t_getters.c
*/
int					get_row_line_start(t_term *trm);
int					get_col_line_end(t_term *trm);
int					get_row_line_end(t_term *trm);

/*
** t_history.c
*/
int					get_next_history_entry(t_term *trm);
int					get_previous_history_entry(t_term *trm);

/*
** t_initialise.c
*/
int					enable_raw_mode(t_term *trm);
int					init_line(char **line);
int					init_term(t_term *trm, char *env);

/*
** t_line_manip.c
*/
int					remove_entire_line(t_term *trm);
int					remove_char(t_term *trm);
int					insert_string(t_term *trm, char *s);
int					insert_chars(t_term *trm, char *buf);

/*
** t_move_cursor_1.c
*/
int					move_cursor_forward(t_term *trm);
int					move_cursor_back(t_term *trm);
int					move_cursor_to_start(t_term *trm);
int					move_cursor_to_end(t_term *trm);

/*
** t_move_cursor_2.c
*/
int					move_cursor_up(t_term *trm);
int					move_cursor_down(t_term *trm);
int					move_cursor_to_start_of_row(t_term *trm);
int					move_cursor_to_end_of_row(t_term *trm);

/*
** t_update_vars.c
*/
int					update_position_trackers(t_term *trm);

/*
** t_utils.c
*/
int					disable_raw_mode(t_term *trm);
void				clear_term(t_term *trm);
int					error_msg(char *error_message);
int					ft_putchar_int(int c);
void				print_prompt(t_term *trm, int quotes);

/*
** term_ctrl.c
*/
int					term_ctrl(t_term *trm, char **line, int quotes);

/*
** tools
*/
int					ft_isatty(int fd);
int					is_redir(int c);
int					get_type(int c);
int					check_fd_stat(int fd);
char				*mini_strjoin(char *s1, char *s2, char *link);

/*
** tree 1
*/
t_node				*build_tree(t_info *info);
t_node				*job(t_info *info);
t_node				*job1(t_info *info);
t_node				*cmd(t_info *info);

/*
** tree 2
*/
int					get_redirection(t_info *info, int type,
						char **fd, char **filename);
t_node				*get_result(int type, char *fd, char *filename);
t_node				*redirection(t_info *info, t_node *save,
						char *fd, char *filename);
t_node				*simplecmd(t_info *info);
t_node				*tokenlist(t_info *info);

/*
** tree tools
*/
int					tree_check_type(t_info *info, int type, char **bufptr);
void				tree_set_params(t_node *node, int type, int fd, char *data);
void				tree_add_branch(t_node *root, t_node *left, t_node *right);
void				tree_del_node(t_node *node);
void				*tree_abort(t_node *left, t_node *right,
						void *tofree, void *freetoo);

#endif
