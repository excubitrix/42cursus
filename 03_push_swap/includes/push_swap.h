/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floogman <floogman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:25:05 by floogman          #+#    #+#             */
/*   Updated: 2021/10/11 09:43:20 by floogman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/includes/libft.h"

# define A 0
# define B 1

# define BUFFER 1024

# define RESET "\033[0m"
# define WHITE "\033[47m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;96m"
# define HONEY "\033[38;5;214m"
# define CLEAR "\033[2J"
# define START "\033[%dF"
# define NEWLINE "\033[K\n"
# define HIDE_CURSOR "\033[?25l"
# define SHOW_CURSOR "\033[?25h"

typedef struct s_info
{
	int		total;
	int		min;
	int		mid;
	int		max;
	int		i_max;
	int		i_2nd_max;
	int		i_min;
	int		steps;
	int		size[2];
	int		size_cpy[2];
	int		*stack[2];
	int		*stack_cpy[2];
	char	*op_str[11];
	void	(*op_ptr[11])(struct s_info *, int **, int *);
	int		rotate_b;
	int		checker;
	int		flag_c;
	int		flag_g;
	int		flag_p;
	int		flag_s;
	int		flag_v;
}				t_info;

int				is_flag(t_info *info, char *arg, int i);
int				print_steps(t_info *info);
int				print_stacks(t_info *info, int **stack, char *op, int pad);

void			print_graph(t_info *info, int pad, int i);
void			print_def(t_info *info, int **stack, int pad, int i);

void			free_all(t_info *info, char *msg);

int				init_stacks(t_info *info, int **stack, int *size, char **nbrs);
void			init_op_ptrs(t_info *info);
void			init_info(t_info *info, int argc, char **argv, int checker);

void			sa(t_info *info, int **stack, int *size);
void			pa(t_info *info, int **stack, int *size);
void			ra(t_info *info, int **stack, int *size);
void			rra(t_info *info, int **stack, int *size);

void			sb(t_info *info, int **stack, int *size);
void			pb(t_info *info, int **stack, int *size);
void			rb(t_info *info, int **stack, int *size);
void			rrb(t_info *info, int **stack, int *size);

void			ss(t_info *info, int **stack, int *size);
void			rr(t_info *info, int **stack, int *size);
void			rrr(t_info *info, int **stack, int *size);

void			move_chunk(t_info *info, int *stack, int size, int limit);
void			sort_three(t_info *info, int **stack);
void			move_b_to_a(t_info *info, int first_dst, int second_dst);
void			push_swap(t_info *info, int chunk_size);

int				pop(int *array, int size);
void			push(int *array, int size, int push);
void			get_indexes(t_info *info, int *stack, int size);
void			index_to_top(t_info *info, int stack, int size, int index);

void			get_min_max(int *stack, int size, int *min, int *max);
void			get_nth_min(int *stack, int size, int n, int *ret);
int				calc_chunk(t_info *info, int chunk_size);
int				get_num(t_info *info, char *num);
int				is_sorted(t_info *info);

#endif
