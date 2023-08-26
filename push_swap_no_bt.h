/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:29:40 by fsusanna          #+#    #+#             */
/*   Updated: 2023/07/20 00:52:29 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define _SA 1
# define _SB 2
# define _SS 3
# define _PA 4
# define _PB 5
# define _RA 6
# define _RB 7
# define _RR 8
# define _RRA 9
# define _RRB 10
# define _RRR 11
# define MAX_BACKTRACK 5
# define ONE_LINE 0
# define NEW_LINE 1
# define CHECK_TURNAROUND 0b011011000000
# define NOT_0A 0b000000100000
# define NOT_0B 0b000000010000
# define NOT_1A 0b101101001010
# define NOT_1B 0b110110001100
# define CLEAN_1A 0b001001000010
# define CLEAN_1B 0b010010000100
# define CLEAN_2A 0b001001000010
# define CLEAN_2B 0b010010000100
# define NOT_2A 0b001001000000
# define NOT_2B 0b010010000000
# define ALL_OPS 0b111111111110

typedef struct s_crawler
{
	char	*steps;
	int	vals;
	int	n;
	int	repeated_op;
	int	times;
	int	in_stack_A;
	int	ordered;
}			t_crawler;

typedef struct s_data
{
	int				id;
	int				val;
	int				target;
	int				golden;
	struct s_data	*prev;
	struct s_data	*next;
}			t_data;

typedef struct s_compendium
{
	int		count_val;
	int		count_golden;
	t_data	**top;
	int	(*ops[12])(struct s_compendium *);
	char	steps[15000];
	int		n_st;
	int		count[2];
	t_data	*s;
}			t_compendium;

int		ft_atoi(char *str, int *err);
void	index(t_compendium *all);
void	quick_st(t_compendium *all);
int		data_atop(t_compendium *all, t_data *mv, int stack);
int		move_sa(t_compendium *all);
int		move_sb(t_compendium *all);
int		move_ss(t_compendium *all);
int		move_pa(t_compendium *all);
int		move_pb(t_compendium *all);
int		move_ra(t_compendium *all);
int		move_rb(t_compendium *all);
int		move_rr(t_compendium *all);
int		move_rra(t_compendium *all);
int		move_rrb(t_compendium *all);
int		move_rrr(t_compendium *all);
void	add_data(t_compendium *all, int position, t_data *on);
void	init(t_compendium *all, int position, int val, int *err);
void	show_tgts(t_compendium *all);
void	show_all(t_compendium *all);
/*void	show_a(t_data **stk);
void	show_b(t_data **stk);
int		dist(t_data *t);
int		trend(t_data *t);*/
void	print_1_step(int op);
void	print_steps(char *ops, int nl);
int		gap(t_compendium *all, t_data *i);
int		longest(t_compendium *all);
int		mean(t_compendium *all, int stk);
int		inter_tension(t_compendium *all);
int		intra_tension(t_compendium *all);
int		tot_tension(t_compendium *all);
int		apply_min(t_compendium *all);
int		undo(t_compendium *all, int n);
int		sense(int a, int b, int max);
int		clean_steps(char *steps, int vals);
void	start(t_compendium *all);
void	try_moves(t_compendium *all);
void	process(t_compendium *all, int stk, int ct, int bit);
int		turnaround(t_crawler *bot);
int		opposite_steps(t_crawler *bot);
int		useless_step(t_crawler *bot);
t_data	**mem_stack(int n);
int		main(int narg, char **args);
/*___Bonus part___*/
#endif
