/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/10 02:09:15 by fsusanna         ###   ########.fr       */
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
/*
void	assign_rev(t_compendium *all, char *vals)
{
	int	i;

	i = -1;
	while (++i < 12)
		all->revert[i] = vals[i] - '0';
}
*/

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
	write(1, "\n", 1);
}


void	print_steps(t_compendium *all)
{
	int		st;

	st = -1;
	while (++st < all->n_st)
		print_1_step(all->steps[st]);
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

int	inter_tension(t_compendium *all)
{
	int		ret;
	t_data	*ia;
	t_data	*ib;
	int		tmp;
	int		ct;

	ret = 0;
	ia = all->top[0];
	ib = all->top[1];
	if (!ia || !ib)
		return (0);
	ct = longest(all);
	tmp = ct / 2;
	while (tmp--)
	{
		ia = ia->prev;
		ib = ib->prev;
	}
	while (ct--)
	{
		ret += gap(ia->target - ib->target, all->max_val);
		ia = ia->next;
		ib = ib->next;
	}
	return (ret);
}

int	intra_tension(t_compendium *all)
{
	int		ret;
	int		id;
	t_data	*t;
	t_data	*i;

	ret = 0;
	id = -1;
	while (++id < 2)
	{
		t = all->top[id];
		if (!t)
			continue ;
		ret += gap(t->target - t->next->target, all->max_val) + id;
		i = t->next;
		while (i != t)
		{
			ret += gap(i->target - i->next->target, all->max_val) + id;
			i = i->next;
		}
	}
	return (ret);
}

int	tot_tension(t_compendium *all)
{
	int		ret;

	ret = inter_tension(all);
	ret += intra_tension(all);
	return (ret);
}

int	apply_min(t_compendium *all)
{
	int	op;
	int	do_op;
	int	ret;

	ret = -1;
	while (ret == -1)
	{
		op = 0;
		do_op = 0;
		ret = all->tns[0] + 1;
		while (++op < 12)
		{
			if (all->tns[op] > -1 && all->tns[op] < all->tns[do_op])
				do_op = op;
		}
		if (!do_op)
			return (-1);
		if ((*(all->ops[do_op]))(all) != do_op)
			all->tns[do_op] = -1;
		ret = all->tns[do_op];
	}
	all->steps[all->n_st] = op;
	all->done[all->n_st] |= 1 << op;
	all->done[all->n_st + 1] = 0;
	all->cut[all->n_st + 1] = all->cut[all->n_st];
	all->cut[all->n_st + 1] &= all->heir_mask[all->steps[all->n_st]];
	all->cut[all->n_st + 1] |= all->cut_mask[all->steps[all->n_st]];
	all->n_st++;
	return (ret);
}

int	undo(t_compendium *all, int n)
{
	int	op;

	all->undo = 1;
	while (n--)
	{
		op = all->revert[(int)all->steps[all->n_st]];
		(*(all->ops[op]))(all);
		all->n_st--;
	}
	all->undo = 0;
}

void	process(t_compendium *all)
{
	int		op;
	t_data	**a;
	t_data	**b;

	index(all);
	a = &(all->top[0]);
	b = &(all->top[1]);
	all->tns[0] = tot_tension(all);
	while (all->tns[0] && all->n_st < 15000 && all->n_st > -1)
	{
		op = 0;
		while (++op < 12)
		{
			all->tns[op] = -1;
			if ((all->done[all->n_st] | all->cut[all->n_st]) & (1 << op))
				continue ;
			(*(all->ops[op]))(all);
			all->tns[op] = tot_tension(all);
			undo(all, 1);
		}
		all->tns[0] = apply_min(all);
		if (all->tns[0] < 0)
			undo(all, 1);

	}
	printf("tens: %i; nb_steps: %i.\n", all->tns[0], all->n_st);
	print_steps(all);
}

/*uso:
 *				(*ops[x])(stk)
 */
void	start(t_compendium *all)
{
	const char	rev[] = {0, 1, 2, 3, 5, 4, 9, 10, 11, 6, 7, 8};
	const int	c_m[] = {0, 14, 14, 14, 5, 4, 2688, 3136, 3584, 1344, 896, 448};
	const int	h_m[] = {0, 3470, 2894, 14, 0, 0,
		3972, 3906, 3584, 3460, 3394, 448};

	all->revert = (char *)rev;
	all->cut_mask = (int *)c_m;
	all->heir_mask = (int *)h_m;
	all->ops[1] = &pr_sa;
	all->ops[2] = &pr_sb;
	all->ops[3] = &pr_ss;
	all->ops[4] = &pr_pa;
	all->ops[5] = &pr_pb;
	all->ops[6] = &pr_ra;
	all->ops[7] = &pr_rb;
	all->ops[8] = &pr_rr;
	all->ops[9] = &pr_rra;
	all->ops[10] = &pr_rrb;
	all->ops[11] = &pr_rrr;
	all->n_st = 0;
	all->done[0] = 0;
	all->cut[0] = 0;
	all->undo = 0;
	process(all);
/*	assign_rev(all, "0123549:;678");*/
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
/*
int	dist(t_data *t)
{
	t_data	*i;
	int		dist;
	int		tmp;

	dist = 0;
	i = t;
	while (i)
	{
		tmp = i->pos - i->target;
		if (tmp < 0)
			tmp *= -1;
		if (tmp > (i->max_val - tmp))
			tmp = i->max_val - tmp;
*		printf("%i ", tmp);*
		dist += tmp;
		i = i->next;
		if (i == t)
			break ;
	}
*	printf("=> %i.\n", dist);*
	return (dist);
}
*/
void	set_top(t_compendium *all, t_data *n)
{
	t_data	*i;

	all->top[n->id] = n;
	n->pos = 0;
	if (n->id)
		i = n->prev;
	else
		i = n->next;
	while (i != n)
	{
		if (n->id)
		{
			i->pos = i->next->pos + 1;
			i = i->prev;
		}
		else
		{
			i->pos = i->prev->pos + 1;
			i = i->next;
		}
	}
}
/*
void	show_all(t_data **stk, int n)
{
	int		i;

	i = -1;
	printf("pos |id  |val |targ|prev|next\n");
	while (++i <= n)
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", stk[i]->pos, stk[i]->id, stk[i]->val, stk[i]->target, (stk[i]->prev - stk[0]), (stk[i]->next - stk[0]));
	}
}

void	show_a(t_data **stk)
{
	t_data	*d;

	d = stk[0]->top[0];
	if (!d)
		return ;
	printf("pos |id  |val |targ|prev|next\n");
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
	d = d->next;
	while (d != d->top[0])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
		d = d->next;
	}
}

void	show_b(t_data **stk)
{
	t_data	*d;

	d = stk[0]->top[1];
	if (!d)
		return ;
	printf("id  |val |targ|prev|next\n");
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
	d = d->next;
	while (d != d->top[1])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
		d = d->next;
	}
}*/
