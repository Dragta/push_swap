/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/05/15 14:39:10 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	direction(t_data *tx, t_data *ty, t_data *tz)
{
	int	ret;
	int	x;
	int	y;
	int	z;

	if (!tx)
		x = ty->target - 1;
	else
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
	(void) max;
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
/*	printf("%i op %i, a: %i b: %i\n", all->n_st - 1, op, all->max[0], all->max[1]);*/
}

int	better_push(t_compendium *all, t_data *i, int tolerance, int method)
{
	int	stack;
	int	sum;

	stack = 1 - i->id;
	if (!all->max[stack])
		return (i->target);
	if (method == 4)
	{
		if (i->target + 1 == all->top[stack]->target || (i->target - all->top[stack]->target == all->max_val - 1))
			return (1);
		return (0);
	}
	if (method == 3)
	{
/*		if (gap(i->target - all->max[stack], all->max_val) < 8 + tolerance)
		if (direction(NULL, i->prev, i) > 0)*/
		if (i->target > i->prev->target || i->prev->target - i->target > all->max_val / 2)
			return (0);
		return (1);
	}
	if (method < 3)
		sum = gap(i->target - all->max[stack], all->max_val);
	else
		sum = gap(i->target - all->top[stack]->target, all->max_val);
	if (sum > all->max_val * tolerance / 100)
		return (0);
	return (1);
}

int	eval_sense(t_compendium *all, int stack, int tolerance, int method)
{
	t_data	*i;
	int		ct;
	int		ret;

	if (!all->max[1 - stack])
		return (0);
	i = all->top[stack];
	ct = 0;
	while (!better_push(all, i, tolerance, method))
	{
		ct++;
		i = i->next;
		if (i == all->top[stack])
			return (-1);
	}
	ret = ct;
	i = all->top[stack];
	ct = 0;
	while (!better_push(all, i, tolerance, method))
	{
		ct++;
		i = i->prev;
		if (i == all->top[stack])
			return (-1);
	}
	if (ct > ret)
		return (0);
	return (3);/*(3)*/
}


void	process(t_compendium *all)
{
	t_data	**top_[2];
	int		stk;
	int		sense;
	int		pass;
	int		toler;

	index(all);
	top_[0] = &(all->top[0]);
	top_[1] = &(all->top[1]);
/*	show_all(all);*/
	stk = 0;
	pass = 0;
	toler = 200 / all->max_val;
	if (toler < 5)
		toler = 5;
	while (++pass < 5)
	{
		if (pass == 3)
			toler = 0;
		while (all->max[stk] > 0 && all->n_st < 12000) /* && (pass < 3 || all->max[1 - stk] < all->max_val / 2))*/
		{
		/*	printf("pass %i, stk %i, steps %i, max0 %i, max1 %i\n", pass, stk, all->n_st, all->max[0], all->max[1]);*/
/*			while (*top_[0] && ((all->max[1] && 
					((*top_[0])->target - 1 == (*top_[0])->prev->target ||
					(!(*top_[0])->target &&
					 (*top_[0])->prev->target == all->max_val))) ||
					(pass == 4 && !all->max[1] && (*top_[0])->target)))
				move(all, _RA);*/
			sense = eval_sense(all, stk, toler, pass);
			if (better_push(all, *top_[stk], toler, pass))
			{
				if ((*top_[1 - stk]) &&
						(((*top_[1])->target > (*top_[0])->target && (*top_[1])->target - (*top_[0])->target < all->max_val / 2) ||
						 ((*top_[1])->target < (*top_[0])->target && (*top_[1])->target - (*top_[0])->target < -all->max_val / 2)))
					move(all, _RB - stk);
				move(all, _PB - stk);
				if (!all->max[stk] || (pass < 4 && eval_sense(all, stk, toler, pass) < 0))
					break ;
				while (pass > 2 && eval_sense(all, stk, toler, pass) < 0)
					toler++;
			}
			else
				move(all, _RA + stk + sense);
/*			{
				if (pass < 3)
					move(all, _RA + stk + sense);
				else
				{
					move(all, _RR + sense);
					toler++;
				}
			}*/
		}
		toler /= 2;
		stk = 1 - stk;
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
/*	printf("%i\n", pass);*/
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
	s = direction(t, i->prev, i);
	trend = 3 * s;
	while (i != t && s * trend > 0)
	{
		trend += s;
		i = i->next;
		s = direction(t, i->prev, i);
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
