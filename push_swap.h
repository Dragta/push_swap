/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:29:40 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/14 10:29:40 by fsusanna         ###   ########.fr       */
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
# define MAX_BACKTRACK 3
# define BLOCK 999999
# define LIMIT 16
# define TOLERANCE 100
# define ONE_LINE 0
# define NEW_LINE 1
# define BACKTRACK_DEPTH 12
# define CHECK_TURNAROUND 0b011011000000
# define NOT_REP 0b011011000000
# define NOT_0A 0b101101101010
# define NOT_0B 0b110110011100
# define NOT_1A 0b101101001010
# define NOT_1B 0b110110001100
# define NOT_2A 0b000001000000
# define NOT_2B 0b000010000000
# define NOT_0TOP_A 0b000101101010
# define NOT_0TOP_B 0b000110011100
# define NOT_1TOP_A 0b000000001010
# define NOT_1TOP_B 0b000000001100
# define NOT_0BTM_A 0b101000000000
# define NOT_0BTM_B 0b110000000000
# define CLEAN_1A 0b001001000010
# define CLEAN_1B 0b010010000100
# define CLEAN_2A 0b001001000010
# define CLEAN_2B 0b010010000100
# define OPS_A 0b001001010010
# define OPS_B 0b010010100100
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
	int				pos;
	int				id;
	int				val;
	int				target;
	int				golden;
	struct s_data	*prev;
	struct s_data	*next;
}			t_data;

typedef struct s_compendium
{
	int		positions;
	int		target_B;
	int		count_val;
	int		count_golden;
	t_data	**top;
	int		(*ops[12])(struct s_compendium *);
	char	*revert;
	char	steps[15000];
	int		done[15000];
	int		cut[15000];
	int		*cut_mask;
	int		*heir_mask;
	int		max_bt;
	int		n_st;
	int		count[2];
	t_data	*block_top[2];
	t_data	*block_btm[2];
	int		count_blocked[2];
	int		min_target;
	int		tns[12];
	int		tolerance;
	char	part[300];
	char	sol[15000];
	int		part_tns;
	int		sol_st;
	t_data	*s;
}			t_compendium;

int		ft_atoi(char *str, int *err);
void	index(t_compendium *all);
void	quick_st(t_compendium *all);
int		data_atop(t_compendium *all, t_data *mv, int stack);
void	count_stacks(t_compendium *all);
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
void	show_pos(t_compendium *all);
void	show_tgts(t_compendium *all);
void	show_all(t_compendium *all);
void	backtrack(t_compendium *all);
/*void	show_a(t_data **stk);
void	show_b(t_data **stk);
int		dist(t_data *t);
int		trend(t_data *t);*/
void	print_1_step(int op);
void	print_steps(char *ops, int nl);
void	move(t_compendium *all, int op);
void	init_next_st(t_compendium *all);
int		gap(int g, int max);
int		longest(t_compendium *all);
int		inter_tension(t_compendium *all);
int		intra_tension(t_compendium *all);
int		tot_tension(t_compendium *all);
int		tot_tension1(t_compendium *all);
int		apply_min(t_compendium *all);
int		undo(t_compendium *all, int n);
void	fan(t_compendium *all, int search_depth);
int		sense(t_data *tx, t_data *ty, t_data *tz);
void	initialise(t_compendium *all);
void	start(t_compendium *all);
void	start_bt(t_compendium *all);
void	try_moves(t_compendium *all);
void	process(t_compendium *all, int stk, int ct, int bit);
t_data	**mem_stack(int n);

int	useless_step(t_crawler *bot);
int	opposite_steps(t_crawler *bot);
int	turnaround(t_crawler *bot);
int	clean_steps(char *steps, int vals);

int		main(int narg, char **args);
/*___Bonus part___*/
#endif
