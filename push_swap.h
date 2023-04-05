/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:29:40 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/05 20:45:50 by fsusanna         ###   ########.fr       */
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
# define OPS_A 0b01001010010
# define OPS_B 0b10010100100

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
	void	(*ops[12])(struct s_compendium *);
	char	*revert;
	char	steps[15000];
	int		done[15000];
	int		cut[15000];
	int		*cut_mask;
	int		*heir_mask;
	int		n_st;
	int		undo;
	int		tns[12];
	t_data	**s;
}			t_compendium;

int		ft_atoi(char *str, int *err);
void	index(t_compendium *all);
void    data_atop(t_data *mv, t_data *on);
void    set_top(t_compendium *all, t_data *n);
void	move_sa(t_compendium *);
void	move_sb(t_compendium *);
void	pr_sa(t_compendium *);
void	pr_sb(t_compendium *);
void	pr_ss(t_compendium *);
void	pr_pa(t_compendium *);
void	pr_pb(t_compendium *);
void	move_ra(t_compendium *);
void	move_rb(t_compendium *);
void	pr_ra(t_compendium *);
void	pr_rb(t_compendium *);
void	pr_rr(t_compendium *);
void	move_rra(t_compendium *);
void	move_rrb(t_compendium *);
void	pr_rra(t_compendium *);
void	pr_rrb(t_compendium *);
void	pr_rrr(t_compendium *);
void    add_data(t_compendium *all, t_data *mv, t_data *on);
void	init(t_compendium *all, t_data *n, int val, int *err);
void	show_all(t_data **stk, int n);
void	show_a(t_data **stk);
void	show_b(t_data **stk);
int		dist(t_data *t);
int		trend(t_data *t);
int		sense(t_data *tx, t_data *ty, t_data *tz);
void	start(t_compendium *all);
void	process(t_compendium *all);
t_data	**mem_stack(int n);
int		main(int narg, char **args);
/*___Bonus part___*/
#endif
