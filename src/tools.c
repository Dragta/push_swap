/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/17 01:31:01 by fsusanna         ###   ########.fr       */
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

void	print_steps(t_compendium *all, int nl)
{
	int		st;
	char	sep;

	if (nl)
		sep = '\n';
	else
		sep = ' ';

	st = -1;
	while (++st < all->n_st)
	{
		print_1_step(all->steps[st]);
		write(1, &sep, 1);
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

int	inter_tension(t_compendium *all)
{
	int		ret;
	t_data	*ia;
	t_data	*ib;
/*	int		tmp;
	int		ct;*/

	ret = 0;
	ia = all->top[0];
	ib = all->top[1];
	if (!ia || !ib)
		return (0);
	ret += gap(ia->target - ib->target, all->max_val);
/*	ct = longest(all);
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
	}*/
	return (ret);
}

int	intra_tension(t_compendium *all)
{
	int		ret;
	int		pos_tns;
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
/*		printf("tn, t: %i, %i\n", t->next->target, t->target);*/
		pos_tns = gap(t->target - t->pos, all->max_val);
		ret += gap(t->pos, all->max_val) * gap(t->next->target - t->target - 1, all->max_val) + id;
/*		printf("intra_tns: %i\n", ret);*/
		i = t->next;
		while (i != t)
		{
/*			printf("in, i: %i, %i\n", i->next->target, i->target);*/
			pos_tns += gap(t->target - t->pos, all->max_val);
			ret += gap(i->next->target - i->target - 1, all->max_val) + id;
/*			printf("intra_tns: %i\n", ret);*/
			i = i->next;
		}
		ret += pos_tns / (all->max_val - 2);
	}
	return (ret);
}

int	tot_tension(t_compendium *all)
{
	int		ret;

	ret = inter_tension(all);
	ret = intra_tension(all);
	return (ret);
}

int	apply_min(t_compendium *all)
{
	int	op;
	int	do_op;
	int	tmp_op;
	int	ret;

	ret = -1;
	while (ret == -1)
	{
		op = 0;
		do_op = 0;
		ret = all->tns[0] + all->max_val;
		while (++op < 12)
		{
/*			printf(">op: %i (tns %i)\n", op, all->tns[op]);*/
			if (all->tns[op] > -1 && all->tns[op] < ret)
			{
				ret = all->tns[op];
/*				printf("%i ->ret\n", ret);*/
				do_op = op;
			}
		}
		if (!do_op)
			return (-1);
		tmp_op = (*(all->ops[do_op]))(all);
		if (tmp_op > 0)
				all->done[all->n_st] |= 1 << tmp_op;
		if (tmp_op != do_op)
			all->tns[do_op] = -1;
		printf("%i ", tmp_op);
		ret = all->tns[tmp_op];
	}
/*	ret += '0';
	write(1, &ret, 1);
	ret -= '0';*/
	if (ret < 0)
		return (ret);
/*	write(1, "(", 1);
	print_1_step(do_op);
	write(1, ")\n", 2);*/
	all->steps[all->n_st] = tmp_op;
	all->done[all->n_st] |= 1 << do_op;
	all->done[all->n_st + 1] = 0;
/*	printf("%i ", all->cut[all->n_st]);*/
	all->cut[all->n_st + 1] = all->cut[all->n_st];
/*	printf("%i ", all->heir_mask[(int)all->steps[all->n_st]]);*/
	all->cut[all->n_st + 1] &= all->heir_mask[(int)all->steps[all->n_st]];
/*	printf("%i ", all->cut_mask[(int)all->steps[all->n_st]]);*/
	all->cut[all->n_st + 1] |= all->cut_mask[(int)all->steps[all->n_st]];
/*	printf("%i ", all->cut[all->n_st + 1]);*/
	all->n_st++;
	return (ret);
}

int	undo(t_compendium *all, int n)
{
	int	op;

	all->undo = 1;
	while (n--)
	{
		op = all->revert[(int)all->steps[all->n_st - 1]];
		if ((*(all->ops[op]))(all) < 0)
			return (n + 1);
		if (--all->n_st == 0)
			break ;
	}
	all->undo = 0;
	return (0);
}

void	process(t_compendium *all)
{
	int		op;
/*	t_data	**a;
	t_data	**b;*/
	int		best;

	index(all);
/*	a = &(all->top[0]);
	b = &(all->top[1]);*/
	show_all(all);
	best = 15000;
	while (all->n_st >= 0)
	{
		all->tns[0] = tot_tension(all);
		while (all->tns[0] > 0 && all->n_st < best && all->n_st > -1)
		{
			op = 0;
			printf("(%i/%i)", all->n_st, best);
			printf("tens: %i_%i\n", all->tns[0], tot_tension(all));
			show_tgts(all);
			quick_st(all);
			write(1, "\n", 1);
			while (++op < 12)
			{
				all->tns[op] = -1;
				if ((all->done[all->n_st] | all->cut[all->n_st]) & (1 << op))
					continue ;
				all->steps[all->n_st] = (*(all->ops[op]))(all);
				if (all->steps[all->n_st] < 0)
					continue ;
				all->n_st++;
				all->tns[op] = tot_tension(all);
				all->tns[(int)all->steps[all->n_st]] = tot_tension(all);
				write(1, "ok.", 3);
				undo(all, 1);
			}
			all->tns[0] = apply_min(all);
	/*		if (all->tns[0] < 0)
				undo(all, 1);*/
		}
		if (!all->tns[0])
		{
			printf("tens: %i_%i; nb_steps: %i.\n", all->tns[0], tot_tension(all), all->n_st);
			print_steps(all, ONE_LINE);
			write(1, "\n", 1);
			show_tgts(all);
			best = all->n_st;
			undo(all, 2);
		}
		else
			undo(all, 1);
	}
}

/*uso:
 *				(*ops[x])(stk)
 */
void	start(t_compendium *all)
{
	const char	rev[] = {0, 1, 2, 3, 5, 4, 9, 10, 11, 6, 7, 8};
	const int	c_m[] = {0, 14, 14, 14, 32, 16, 2688, 3136, 3584, 1344, 896, 448};
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
	all->done[0] = 0;
	all->cut[0] = 0;
	all->undo = 0;
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
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", i->pos, i->id, i->val, i->target, (i->prev - all->s[0]), (i->next - all->s[0]));
	i = i->next;
	while (i != all->top[0])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", i->pos, i->id, i->val, i->target, (i->prev - all->s[0]), (i->next - all->s[0]));
		i = i->next;
	}
}
