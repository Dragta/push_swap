/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:25 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	sense(t_data *tx, t_data *ty, t_data *tz)
{
	int	ret;
	int	x;
	int	y;
	int	z;
	
	x = tx->target;
	y = ty->target;
	z = tz->target;
	ret = 1;
	if (x == y || y == z || z == x)
		ret = 0;
	else if ((x > y && y > z) || (z > x && x > y) || (y > z && z > x))
		ret = -1;
	return (ret);
}

void	print_1_step(int op)
{
	if (op < 1 || op > 11)
		return ;
	if (op ==  3)
		write(1, "s", 1);
	if (op < 4)
		write(1, "s", 1);
	else if (op < 6)
		write(1, "p", 1);
	else
		write(1, "r", 1);
	if (op > 7)
		write(1, "r", 1);
	if (OPS_A & (1 << op))
		write(1, "a", 1);
	if (OPS_B & (1 << op))
		write(1, "b", 1);
	if (op ==  11)
		write(1, "r", 1);
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

void	quick_st(t_compendium *all)
{
	int i;
	int	tmp;

	i = 0;
	while (i < all->n_st)
	{
		tmp = all->steps[i++] + '0';
		write(1, &tmp, 1);
	}
}

int	gap(int g, int max)
{
	if (g < 0)
		g = -g;
	if (g > max / 2)
		g = max - g;
	return (g);
}

int	longest(t_compendium *all)
{
	t_data	*i;
	int		tmp;
	int		ct;
	int		s;

	s = -1;
	ct = 0;
	while (++s < 2)
	{
		i = all->top[s];
		if (i)
		{
			tmp = 1;
			while (i->next != all->top[s])
			{
				tmp++;
				i = i->next;
			}
		}
		if (tmp > ct)
			ct = tmp;
	}
	return (ct);
}

void	init_next_st(t_compendium *all)
{
	all->steps[all->n_st + 1] = 0;
/*	all->done[all->n_st + 1] = 0;
	all->cut[all->n_st + 1] = all->cut[all->n_st];
	all->cut[all->n_st + 1] &= all->heir_mask[(int)all->steps[all->n_st]];
	all->cut[all->n_st + 1] |= all->cut_mask[(int)all->steps[all->n_st]];*/
	all->n_st++;
	count_stacks(all);
}
/*
int	apply_min(t_compendium *all)
{
	int	do_op;
	int	tmp_op;
	int	ret;

	ret = -1;
	while (ret == -1)
	{
		do_op = 0;
		ret = min_step(all, &do_op);
		if (!do_op)
			return (-1);
		tmp_op = (*(all->ops[do_op]))(all);
		ret = all->tns[tmp_op];
*		if (all->tolerance > 999)
			printf(" %i>%i(%i)\n", all->n_st, do_op, ret);*
		if (tmp_op > 0)
		{
			all->done[all->n_st] |= 1 << tmp_op;
			all->tns[tmp_op] = -1;
		}
		if (tmp_op != do_op)
		{
			printf("*****\ndo_op: %i; tmp_op: %i\n*****", do_op, tmp_op);
			all->done[all->n_st] |= 1 << do_op;
			all->tns[do_op] = -1;
		}
	}
	all->steps[all->n_st] = tmp_op;
	init_next_st(all);
	return (ret);
}
*/
void	exclude_reps(t_compendium *all)
{
	int	id;
	int	msk;
	int	op;
	int	i;

	op = 0;
	msk = NOT_REP;
	while (msk)
	{
		op++;
		msk = msk >> 1;
		if (!(msk & 1))
			continue ;
		id = 1;
		if (OPS_A & (1 << op))
			id = 0;
		i = all->max[id] / 2;
		while (i && i <= all->n_st && all->steps[all->n_st - i] == op)
			i--;
		if (!i)
			all->cut[all->n_st] |= 1 << op;
	}
}

int	exclude(t_compendium *all)
{
	int	ret;

	exclude_reps(all);
	ret = 0;
	if (!all->max[0])
		ret |= NOT_0A;
	if (!all->max[1])
		ret |= NOT_0B;
	if (all->max[0] < 2)
		ret |= NOT_1A;
	if (all->max[1] < 2)
		ret |= NOT_1B;
	if (all->max[0] < 3)
		ret |= NOT_2A;
	if (all->max[1] < 3)
		ret |= NOT_2B;
	ret |= all->done[all->n_st];
	ret |= all->cut[all->n_st];
	return (ret);
}
/*
int	undo(t_compendium *all, int n)
{
	int	op;

	n++;
	while (--n)
	{
		if (!all->n_st)
		{
			n = -1;
			break ;
		}
		op = all->revert[(int)all->steps[all->n_st - 1]];
		if ((*(all->ops[op]))(all) <= 0)
		{
			printf("No undo %i with %i possible. Stack A: %i; Stack B: %i\n", all->steps[all->n_st - 1], op, all->max[0], all->max[1]);
			break ;
		}
		all->steps[all->n_st - 1] = 0;
		all->n_st--;
	}
	all->tns[0] = tot_tension(all);
	if (exclude(all) == ALL_OPS)
		all->tns[0] = -1;
	return (n);
}
*/
void	save_sol(t_compendium *all, int bt_n)
{
	int	i;

	all->sol_tns = all->tns[0];
/*	if (!all->sol_tns)
		quick_st(all);
	printf(" mejor tns: %i\n", all->sol_tns);*/
	i = all->n_st;
	all->sol_part[i - bt_n] = 0;
	while (--i >= bt_n)
		all->sol_part[i - bt_n] = all->steps[i];
}

void	move(t_compendium *all, int op)
{
	(*(all->ops[op]))(all);
	all->steps[all->n_st] = op;
	init_next_st(all);
}

int	better_push(t_compendium *all, int stack, int tolerance)
{
	t_data	*b;
	int	sum;
	int	ret;

	ret = 1;
	b = all->top[1 - stack];
	sum = gap(b->target - all->max[stack], all->max_val);
	if (sum > all->max_val * tolerance / 100)
		ret = 0;
	return (ret);
}

void	process(t_compendium *all)
{
	t_data	**a;
	t_data	**b;
	int		n;
	int		toler;

	index(all);
	a = &(all->top[0]);
	b = &(all->top[1]);
/*	show_all(all);*/
	toler = 20;
	while (all->n_st < 16 * all->max_val && toler > 0)
	{
		n = all->n_st;
		while ((*a) && (*a)->next != all->top[0] && all->n_st - n < 6 * all->max_val)
		{
			if (better_push(all, 1, toler))
			{
				if ((*b) && (*b)->target > (*a)->target)
					move(all, _RB);
				move(all, _PB);
			}
			else
				move(all, _RA);
		}
		toler -= 3;
		while ((*b) && (*b)->next != all->top[1] && all->n_st - n < 12 * all->max_val)
		{
			if (better_push(all, 0, toler))
			{
				if ((*a) && (*a)->target < (*b)->target)
					move(all, _RA);
				move(all, _PA);
			}
			else
				move(all, _RB);
		}
		toler -= 3;
	}


	
/*	save_sol(all, 0);
	undo(all, all->n_st);
	i = -1;
	while (all->sol_part[++i])
	{
		op = all->sol_part[i];
		(*(all->ops[(int)op]))(all);
		all->done[all->n_st] |= 1 << op;
		all->steps[all->n_st] = op;
		init_next_st(all);
		print_1_step(op);
		printf("\n%i (%i)\n", all->n_st, tot_tension(all));
	}*/
	print_steps(all->steps, NEW_LINE);
/*	printf("%i\n", toler);*/
}

/*uso:
 *				(*ops[x])(stk)
 */
void	start(t_compendium *all)
{
	const char	rev[] = {0, 1, 2, 3, 5, 4, 9, 10, 11, 6, 7, 8};
	const int	c_m[] = {0, 14, 14, 14, 32, 16,
		2688, 3136, 3584, 1344, 896, 448};
	const int	h_m[] = {0, 3470, 2894, 14, 0, 0,
		3972, 3906, 3584, 3460, 3394, 448};

	all->revert = (char *)rev;
	all->cut_mask = (int *)c_m;
	all->heir_mask = (int *)h_m;
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
	all->done[0] = 0;
	all->cut[0] = 0;
	all->tolerance = TOLERANCE;
	process(all);
}

int	trend(t_data *t)
{
	t_data	*i;
	int		s;
	int		trend;

	if (!t)
		return (0);
	i = t->next;
	if (i == t)
		return (1);
	trend = 2;
/*	if(i->target < t->target && t->target - i->target > t->max_val / 2)*/
	if(i->target < t->target)
		trend = -2;
	if (i->next == t)
		return (trend);
	i = i->next;
	s = sense(t, i->prev, i);
	trend = 3 * s;
	while (i != t && s * trend > 0)
	{
		trend += s;
		i = i->next;
		s = sense(t, i->prev, i);
	}
	return (trend);
}

void	count_stacks(t_compendium *all)
{
	t_data	*i;
	int		p;
	int		s;

	s = -1;
	while (++s < 2)
	{
		i = all->top[s];
		all->max[s] = 0;
		if (!i)
			continue ;
		p = 0;
		i->pos = p++;
		if (s)
			i = i->prev;
		else
			i = i->next;
		while (i != all->top[s])
		{
			i->pos = p++;
			if (s)
				i = i->prev;
			else
				i = i->next;
		}
		all->max[s] = p;
/*		all->max[s] = all->max_val;*/
	}
}

void	show_tgts(t_compendium *all)
{
	t_data	*i;
	int		s;
	char	tmp;

	s = -1;
	while (++s < 2)
	{
		if (s)
			write(1, " // b: ", 7);
		else
			write(1, "a: ", 3);
		i = all->top[s];
		if (!i)
			continue ;
		tmp = '0' + i->target;
		write(1, &tmp, 1);
		while (i->next != all->top[s])
		{
			i = i->next;
			tmp = '0' + i->target;
			write(1, " ", 1);
			write(1, &tmp, 1);
		}
	}
	write(1, "\n", 1);
}

void	show_all(t_compendium *all)
{
	t_data	*i;

	i = all->top[0];
	printf("pos |id  |val |targ|prev|next\n");
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", i->pos, i->id, i->val, i->target, (i->prev - &(all->s[0])), (i->next - &(all->s[0])));
	i = i->next;
	while (i != all->top[0])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", i->pos, i->id, i->val, i->target, (i->prev - &(all->s[0])), (i->next - &(all->s[0])));
		i = i->next;
	}
}
