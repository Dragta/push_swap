/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:29:40 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/27 16:07:15 by fsusanna         ###   ########.fr       */
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
# define LIMITE 500
# define TOLERANCE 20
# define ONE_LINE 0
# define NEW_LINE 1
# define BACKTRACK_DEPTH 5
# define NOT_1A 0b101101001010
# define NOT_1B 0b110110001100
# define NOT_2A 0b001001000000
# define NOT_2B 0b010010000000
# define OPS_A 0b001001010010
# define OPS_B 0b010010100100
# define ALL_OPS 0b111111111110

typedef struct s_data
{
	int				pos;
	int				id;
	int				val;
	int				target;
	struct s_data	*prev;
	struct s_data	*next;
}			t_data;

typedef struct s_compendium
{
	int		max_val;
	t_data	**top;
	int	(*ops[12])(struct s_compendium *);
	char	*revert;
	char	steps[15000];
	int		done[15000];
	int		cut[15000];
	int		*cut_mask;
	int		*heir_mask;
	int		n_st;
	int		max[2];
	int		tns[12];
	char	sol_part[30];
	int		sol_tns;
	t_data	**s;
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
void	add_data(t_compendium *all, t_data *mv, t_data *on);
void	init(t_compendium *all, t_data *n, int val, int *err);
void	show_tgts(t_compendium *all);
void	show_all(t_compendium *all);
/*void	show_a(t_data **stk);
void	show_b(t_data **stk);
int		dist(t_data *t);
int		trend(t_data *t);*/
void	print_1_step(int op);
void	print_steps(char *ops, int nl);
int		gap(int g, int max);
int		longest(t_compendium *all);
int		inter_tension(t_compendium *all);
int		intra_tension(t_compendium *all);
int		tot_tension(t_compendium *all);
int		apply_min(t_compendium *all);
int		undo(t_compendium *all, int n);
int		sense(t_data *tx, t_data *ty, t_data *tz);
void	start(t_compendium *all);
void	try_moves(t_compendium *all);
void	process(t_compendium *all);
t_data	**mem_stack(int n);
int		main(int narg, char **args);
/*___Bonus part___*/
#endif
