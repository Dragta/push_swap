/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 13:08:02 by fsusanna         ###   ########.fr       */
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

void	move(t_compendium *all, int op)
{
	int	op_done;

	op_done = (*(all->ops[op]))(all);
	all->steps[all->n_st] = op_done;
	all->steps[all->n_st + 1] = 0;
	all->done[all->n_st + 1] = 0;
	all->cut[all->n_st + 1] = all->cut[all->n_st];
	all->cut[all->n_st + 1] &= all->heir_mask[(int)all->steps[all->n_st]];
	all->cut[all->n_st + 1] |= all->cut_mask[(int)all->steps[all->n_st]];
	all->n_st++;
	count_stacks(all);
/*	printf("n=%i (op %i)\n", all->n_st, op);
	print_1_step(op);
	printf("\n");*/
}
/*
t_data	*find_last (t_compendium *all, int bit)
{
	t_data	*ret;

	ret = all->top[0]->prev;
	while (ret->golden & 1 << (bit + 1))
		ret = ret->prev;
	return (ret);
}
*/
void	order_2_plus(t_compendium *all, int stk)
{
	t_data	**this;

	if (stk)
	{
		move(all, _PA);
		move(all, _PA);
	}
	this = &(all->top[0]);
	if ((*this)->golden > (*this)->next->golden)
		move(all, _SA);
}

void	order_2_minus(t_compendium *all, int stk)
{
	t_data	**this;

	this = &(all->top[stk]);
	move(all, _RRA + stk);
	if (stk)
	{
		if ((*this)->golden < (*this)->prev->golden)
		{
			move(all, _RRB);
			move(all, _PA);
		}
		else
		{
			move(all, _PA);
			move(all, _RRB);
		}
		move(all, _PA);
	}
	else
		move(all, _RRA);
	if (!stk && (*this)->golden > (*this)->next->golden)
		move(all, _SA);
}
/*
int	factorial(int n)
{
	if (!n)
		return (1);
	else
		return (n * factorial(n - 1));
}

int	reduce(int *targets, int tmp)
{
	int	f;
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	f = factorial(tmp);
	while (++i < tmp * (tmp - 1))
	{
		if (!(i % tmp))
			f /= tmp - i / tmp;
		if (i / tmp < i % tmp && targets[i % tmp] < targets[i / tmp])
			ret += f;
	}
	return (ret);
}

void	order_last5(t_compendium *all, int stk, int tmp, int sgn)
{
	int	sequence;
	int	targets[5];
	int	i;

	i = -1;
	while (++i < tmp)
	{
		if (sgn < 0)
			elem = elem->prev;
		targets[i] = elem->target;
		if (sgn > 0)
			elem = elem->next;
	}

	sequence = reduce(targets, stk, tmp);
}

void	order_last(t_compendium *all, int stk, int tmp, int sgn)
{
	if (1 == tmp && sgn < 0)
		move(all, _RRA + stk);
	if (1 == tmp && stk)
		move(all, _PA);
	if (2 == tmp && sgn > 0)
		order_2_plus(all, stk);
	if (2 == tmp && sgn < 0)
		order_2_minus(all, stk);
}
*/

int	min_target(t_compendium *all, int stk, int tmp, int sgn)
{
	t_data	*i;
	int	ret;

	i = all->top[stk];
	if (sgn < 0)
		i = i->prev;
	ret = i->target;
	while (--tmp)
	{
		if (sgn < 0)
			i = i->prev;
		else
			i = i->next;
		if (i->target < ret)
			ret = i->target;
	}
	return (ret);
}

void	set_blocks(t_compendium *all, int stk, int tmp, int sgn)
{
	int	t;

	t = tmp;
	all->count_blocked[1 - stk] = all->count[1 - stk];
	all->block_top[1 - stk] = all->top[1 - stk];
	if (all->top[1 - stk])
	{
		all->block_btm[1 - stk] = all->top[1 - stk]->prev;
/*		printf("stk %i, blktop=%i, blkbtm=%i\n", 1-stk, all->block_top[1 - stk]->target, all->block_btm[1 - stk]->target);*/
	}
	else
		all->block_btm[1 - stk] = NULL;
	all->count_blocked[stk] = all->count[stk] - tmp;
	if (all->count_blocked[stk])
	{
		all->block_top[stk] = all->top[stk];
		all->block_btm[stk] = all->top[stk]->prev;
		while (sgn < 0 && t--)
			all->block_btm[stk] = all->block_btm[stk]->prev;
		while (sgn > 0 && t--)
			all->block_top[stk] = all->block_top[stk]->next;
/*		printf("stk %i, blktop=%i, blkbtm=%i\n", stk, all->block_top[stk]->target, all->block_btm[stk]->target);*/
	}
	else
	{
		all->block_top[stk] = NULL;
		all->block_btm[stk] = NULL;
	}
	all->min_target = min_target(all, stk, tmp, sgn);
/*	printf("min: %i\n", all->min_target);*/
}

void	order_last(t_compendium *all, int stk, int tmp, int sgn)
{
/*	printf("order_last: stk %i, tmp %i, sgn %i\n", stk, tmp, sgn);
	printf("_____ IN: n=%i, ct0 %i, ct1 %i\n", all->n_st, all->count[0], all->count[1]);*/
	set_blocks(all, stk, tmp, sgn);
	start_bt(all);
/*	backtrack(all);*/
/*	printf("_____OUT: n=%i\n", all->n_st);*/
	all->count_blocked[0] = 0;
	all->count_blocked[1] = 0;
	all->block_top[0] = NULL;
	all->block_top[1] = NULL;
}

/*order_last alternativa{
	int	err;
	int	i;
	t_compendium	part;
	t_data			a;
	t_data			stack[MAX_BACKTRACK + 2];
	t_data			*top[2];

	err = 0;
	part.count_val = tmp + 2;
	part.count_golden = phi(part.count_val);
	part.top = top;
	part.s = stack;
	top[stk] = part.s + tmp * (1 - sgn) / 2;
	top[1 - stk] = part.s + tmp + 1;
	a = all->top[stk];
	i = -1;
	while (sgn < 0 && ++i < tmp)
		a = a->prev;
	i = -1;
	while (++i < tmp)
	{
		init(&part, i, a->target, &err);
		a = a->next;
	}
*	if (narg == 3)
	{
		all.count[0] = 500;
		printf("mean: %i\n", mean(&all, 0));
	}*
		start(&part);
}*/

int	fuse(t_compendium *all, int stk, int tmp, int sgn)
{
	t_data	*d;
	int		or;
	int		and;
	int		ret;

	d = all->top[stk];
	if (sgn < 0)
		d = d->prev;
	or = d->golden;
	and = d->golden;
	if (sgn > 0)
		d = d->next;
	while (--tmp)
	{
		if (sgn < 0)
			d = d->prev;
		or |= d->golden;
		and &= d->golden;
		if (sgn > 0)
			d = d->next;
	}
	or ^= 0xFFFF;
	ret = and | or;
	return (ret);
}

int	separate(t_compendium *all, int stk, int tmp, int sgn, int bit)
{
	int	digit;
	int	ret;
	int	fused_val;

	fused_val = fuse(all, stk, tmp, sgn);
/*	printf("separate: stk %i, tmp %i, sgn %i, bit %i", stk, tmp, sgn, bit);*/
	while (bit > 0 && (fused_val & (1 << bit)))
		bit--;
/*	printf("\n_____ IN: n=%i, ct0 %i, ct1 %i\n", all->n_st, all->count[0], all->count[1]);*/
	ret = 0;
	while (tmp--)
	{
		if (sgn < 0)
			move(all, _RRA + stk);
		digit = (all->top[stk]->golden & (1 << bit)) / (1 << bit);
		if (stk == digit || sgn > 0)
		{
			move(all, _PB + 2 * stk + digit - 4 * stk * digit);
/*			printf("%i.", _PB + 2 * stk + digit - 4 * stk * digit);*/
		}
		ret += digit;
	}
/*	printf("_____OUT: n=%i\n\n", all->n_st);
	printf("\n\n");*/
	return (ret);
}


void	process(t_compendium *all, int stk, int ct, int bit)
{
	int		tmp;
	int		ct1;
	int		sgn;

	if (!ct)
		return ;
	sgn = 1;
	if (ct < 0)
		sgn = -1;
	tmp = sgn * ct;
	if (tmp <= all->max_bt) /*<5 => backtracking*/
		order_last(all, stk, tmp, sgn);
	if (tmp <= all->max_bt || bit < 0)
		return ;
	ct1 = separate(all, stk, tmp, sgn, bit);
	if (stk || ct1 == all->count[0] || sgn < 0)
		process(all, 0, ct1, bit - 2);
	else
		process(all, 0, -ct1, bit - 2);
	if (!stk || tmp - ct1 == all->count[1] || sgn < 0)
		process(all, 1, tmp - ct1, bit - 1);
	else
		process(all, 1, -(tmp - ct1), bit - 1);
}

/*uso:
 *				(*ops[x])(stk)
 */
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

void	start(t_compendium *all)
{
	int		bit;
	const char	rev[] = {0, 1, 2, 3, 5, 4, 9, 10, 11, 6, 7, 8};
	const int	c_m[] = {0, 14, 14, 14, 32, 16, 2688, 3136, 3584, 1344, 896, 448};
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
	bit = 2;
	while (1 << (bit + 1) <= all->count_golden)
		bit++;
	process(all, 0, all->count_val, bit);
	all->n_st = clean_steps(all->steps, all->count_val);
	print_steps(all->steps, NEW_LINE);
}

void	show_pos(t_compendium *all)
{
	t_data	*i;
	int		s;
/*	char	tmp;*/

	s = -1;
	while (++s < 2)
	{
		if (s)
			write(1, " // b: ", 7);
		else
			write(1, "\na: ", 4);
		i = all->top[s];
		if (!i)
			continue ;
/*		tmp = '0' + i->pos;
		write(1, &tmp, 1);*/
		printf("%i", i->pos);
		while (i->next != all->top[s])
		{
			i = i->next;
/*			tmp = '0' + i->pos;
			write(1, " ", 1);
			write(1, &tmp, 1);*/
			printf(" %i", i->pos);
		}
	}
	write(1, " (pos)\n", 7);
/*	tot_tension1(all);*/
}

void	show_tgts(t_compendium *all)
{
	t_data	*i;
	int		s;
/*	char	tmp;*/

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
/*		tmp = '0' + i->target;
		write(1, &tmp, 1);*/
		printf("%i", i->target);
		while (i->next != all->top[s])
		{
			i = i->next;
/*			tmp = '0' + i->target;
			write(1, " ", 1);
			write(1, &tmp, 1);*/
			printf(" %i", i->target);
		}
	}
	show_pos(all);
	write(1, "\n", 1);
}
