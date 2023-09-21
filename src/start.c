/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 18:42:02 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_1_step(int op)
{
	char	*ops;

	if (op < 1 || op > 11)
		return ;
	ops = "xx  sa  sb  ss  pa  pb  ra  rb  rr  rra rrb rrr";
	if (op < 9)
		write(1, ops + 4 * op, 2);
	else
		write(1, ops + 4 * op, 3);
}

void	print_steps(char *ops, int nl)
{
	char	sep;

	sep = ' ';
	if (nl)
		sep = '\n';
	while (*ops)
	{
		print_1_step(*ops);
		write(1, &sep, 1);
		ops++;
	}
}

void	initialise(t_compendium *all)
{
	all->ops[1] = &move_sa;
	all->ops[2] = &move_sb;
	all->ops[3] = &move_ss;
	all->ops[4] = &move_pa;
	all->ops[5] = &move_pb;
	all->ops[6] = &move_ra;
	all->ops[7] = &move_rb;
	all->ops[8] = &move_rr;
	all->ops[9] = &move_rra;
	all->ops[10] = &move_rrb;
	all->ops[11] = &move_rrr;
	all->n_st = 0;
	all->steps[0] = 0;
	all->count_blocked[0] = 0;
	all->count_blocked[1] = 0;
}

void	index(t_compendium *all)
{
	t_data	*tmp;
	int		i;

	tmp = all->top[0];
	tmp->target = 0;
	tmp = tmp->next;
	i = 1;
	while (tmp != all->top[0])
	{
		tmp->target = i++;
		tmp->golden = phi(i);
		tmp = tmp->next;
	}
	all->count[0] = i;
	all->s[0].prev = &(all->s[i - 1]);
	all->s[i - 1].next = &(all->s[0]);
	while (--i)
	{
		all->s[i].prev = &(all->s[i - 1]);
		all->s[i - 1].next = &(all->s[i]);
	}
	all->top[0] = all->s;
	count_stacks(all);
}

void	start(t_compendium *all)
{
	t_group		group;
	const char	rev[] = {0, 1, 2, 3, 5, 4, 9, 10, 11, 6, 7, 8};
	const int	c_m[] = {0, 14, 14, 14, 32, 16,
		2688, 3136, 3584, 1344, 896, 448};
	const int	h_m[] = {0, 3470, 2894, 14, 0, 0,
		3972, 3906, 3584, 3460, 3394, 448};

	index(all);
	initialise(all);
	all->revert = (char *)rev;
	all->cut_mask = (int *)c_m;
	all->heir_mask = (int *)h_m;
	all->max_bt = MAX_BACKTRACK;
	if (all->count_val < 101)
		all->max_bt = 5;
	group.bit = 2;
	while (1 << (group.bit + 1) <= all->count_golden)
		group.bit++;
	group.stk = 0;
	group.tmp = all->count_val;
	group.sgn = 1;
	process(all, group);
	all->n_st = clean_steps(all->steps, all->count_val);
	print_steps(all->steps, NEW_LINE);
}
