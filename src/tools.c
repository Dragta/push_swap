/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/27 18:58:47 by fsusanna         ###   ########.fr       */
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

int	inter_tension(t_compendium *all)
{
	int		lim;
	int		d;
	int		ret;
	t_data	*ia;
	t_data	*ib;
/*	int		tmp;
	int		ct;*/

	ret = 0;
	lim = (all->max_val + 44) * 9;
	lim = 98 * all->max_val / lim;
	ia = all->top[0];
	ib = all->top[1];
	if (!ia || !ib)
		return (0);
/*	ret += gap(ia->target - ib->target, all->max_val);*/

	d = gap(ia->target - ib->target, all->max_val);
	if (d < lim)
		ret += (lim - d) * gap(ia->pos, all->max[0]) * gap(ia->pos, all->max[0]);
	ia = ia->next;
	while (ia != all->top[0])
	{
		d = gap(ia->target - ib->target, all->max_val);
		if (d < lim)
			ret += (lim - d) * gap(ia->pos, all->max[0]) * gap(ia->pos, all->max[0]);
		ia = ia->next;
	}
	d = gap(ia->target - ib->target, all->max_val);
	if (d < lim)
		ret += (lim - d) * gap(ib->pos, all->max[1]) * gap(ib->pos, all->max[1]);
	ib = ib->next;
	while (ib != all->top[1])
	{
		d = gap(ia->target - ib->target, all->max_val);
		if (d < lim)
			ret += (lim - d) * gap(ib->pos, all->max[1]) * gap(ib->pos, all->max[1]);
		ib = ib->next;
	}

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

int	point_tns(t_compendium *all, t_data *i)
{
	int		ret;

	ret = gap(i->next->target - i->target + (2 * i->id - 1), all->max_val) + i->id;
	ret *= gap(i->pos, all->max_val) + 1;
	if (!i->id || ret > 5 || all->max[i->id] > all->max_val / 2)
		ret *= 3;
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
	pos_tns = 0;
	id = -1;
	while (++id < 2)
	{
		t = all->top[id];
		if (!t)
			continue ;
/*		printf("tn, t: %i, %i\n", t->next->target, t->target);*/
/*		i = t->next->next;
		while (id && all->max[id] > 2 && sense(t, t->next, t->next->next) == sense(t, t->next, i))*/
		pos_tns += gap(t->target - t->pos, all->max_val);
		ret += point_tns(all, t);
		i = t->next;
/*		ret += gap(t->pos, all->max[id]) * gap(t->pos, all->max[id]) * gap(t->next->target - t->target + (2 * id - 1), all->max[id]); + id;*/
/*		printf("intra_tns: %i\n", ret);*/
		while (i != t)
		{
/*			printf("target, pos, max: %i, %i, %i\n", i->target, i->pos, all->max_val);*/
			pos_tns += gap(i->target - i->pos, all->max_val);
			ret += point_tns(all, i);
/*			printf("intra_tns: %i\n", ret);*/
			i = i->next;
		}
	}
/*	ret *= all->max[0] - all->max[1];
	if (ret < 0)
		ret *= -1;*/
	if (!ret)
		ret += pos_tns / all->max_val;
	return (ret);
}

int	tot_tension(t_compendium *all)
{
	int		ret;

/*	ret = inter_tension(all);
	printf("inter(%i) \n", ret);*/
	ret = intra_tension(all);
	return (ret);
}

int	min_step(t_compendium *all, int *op)
{
	int	ret;
	int	low;

	ret = all->tns[0] + TOLERANCE;
/*	ret = 15000;*/
	low = 12;
	while (--low)
	{
		if (all->tns[low] > -1 && all->tns[low] < ret)
		{
			ret = all->tns[low];
			*op = low;
		}
	}
	return (ret);
}

void	init_next_st(t_compendium *all)
{
	all->steps[all->n_st + 1] = 0;
	all->done[all->n_st + 1] = 0;
	all->cut[all->n_st + 1] = all->cut[all->n_st];
	all->cut[all->n_st + 1] &= all->heir_mask[(int)all->steps[all->n_st]];
	all->cut[all->n_st + 1] |= all->cut_mask[(int)all->steps[all->n_st]];
	all->n_st++;
}

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
		if (tmp_op > 0)
		{
			all->done[all->n_st] |= 1 << tmp_op;
			all->tns[tmp_op] = -1;
		}
		if (tmp_op != do_op)
		{
			all->done[all->n_st] |= 1 << do_op;
			all->tns[do_op] = -1;
		}
	}
/*	if (ret < 0)
		return (ret);*/
	all->steps[all->n_st] = tmp_op;
/*	if (tmp_op != do_op)
		printf("*");
	printf("apply do_op %i ", do_op);*/
	init_next_st(all);
/*	quick_st(all);
	printf("\n");*/
	return (ret);
}

int	exclude_reps(t_compendium *all, int op)
{
	int	id;
	int	i;
	int	ret;

	ret = 0;
	id = 1;
	if (OPS_A && (1 << op))
		id = 0;
	i = all->max[0] / 2;
	while (i && all->steps[all->n_st] == _RA)
		i--;
	if (i)
		ret = 1 << _RA;
}

int	exclude(t_compendium *all)
{
	int	ret;

	ret = 0;
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
/*	exclude_reps*************************/
	return (ret);
}

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
			break ;
		all->n_st--;
	}
	all->tns[0] = tot_tension(all);
	if (exclude(all) == ALL_OPS)
		all->tns[0] = -1;
	return (n);
}


void	eval_moves(t_compendium *all)
{
	int	op;

/*	quick_st(all);
	printf("w(%i/%i)", all->tns[0], all->sol_tns);*/
	op = 12;
	while (--op)
	{
		all->tns[op] = -1;
		if (exclude(all) & (1 << op))
			continue ;
		all->steps[all->n_st] = (*(all->ops[op]))(all);
		if (all->steps[all->n_st] <= 0)
			continue ;
		if (all->steps[all->n_st] == op)
			all->tns[op] = tot_tension(all);
/*		printf(" %i(%i)", op, all->tns[op]);*/
		all->n_st++;
		undo(all, 1);
	}
/*	printf("\n");*/
}

void	save_sol(t_compendium *all, int bt_n)
{
	int	i;

	all->sol_tns = all->tns[0];
/*	if (!all->sol_tns)
		quick_st(all);
	printf(" mejor tns: %i\n", all->sol_tns);*/
	i = all->n_st + 1;
	while (--i >= bt_n)
		all->sol_part[i - bt_n] = all->steps[i];
}


void	process(t_compendium *all)
{
	int		i;
/*	t_data	**a;
	t_data	**b;*/
	int		op;
	int		bt_n;
	int		sol_depth;

	index(all);
/*	a = &(all->top[0]);
	b = &(all->top[1]);
	show_all(all);*/
	all->sol_part[0] = 0;
	all->sol_tns = 2000;
	all->tns[0] = tot_tension(all);
	sol_depth = BACKTRACK_DEPTH;
	while (all->tns[0] && all->n_st < LIMITE)
	{
		bt_n = all->n_st;
		while (bt_n < all->n_st || all->tns[0] > 0)
		{
			eval_moves(all);
			all->tns[0] = apply_min(all);
			if (all->tns[0] > -1 && all->tns[0] <= all->sol_tns)
			{
				if (!all->tns[0] && all->n_st - bt_n < sol_depth)
					sol_depth = all->n_st - bt_n - 1;
				save_sol(all, bt_n);
			}
			if ((all->n_st - bt_n >= sol_depth || all->tns[0] < 0) &&
					all->n_st > bt_n)
				undo(all, 1);
		}
		if (bt_n != all->n_st)
		{
			printf("Error de BackTracking, bt_n(%i) n_st(%i)\n", bt_n, all->n_st);
/*			return ;*/
			break ;
		}
		i = -1;
		if (!all->sol_part[0] && all->n_st)
			undo(all, 1);
		while (all->sol_part[++i])
		{
			op = all->sol_part[i];
			(*(all->ops[op]))(all);
			all->steps[all->n_st] = op;
			init_next_st(all);
		}
		all->sol_part[0] = 0;
		all->tns[0] = tot_tension(all);
	}
	print_steps(all->steps, NEW_LINE);
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
	all->steps[0] = 0;
	all->done[0] = 0;
	all->cut[0] = 0;
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
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", i->pos, i->id, i->val, i->target, (i->prev - all->s[0]), (i->next - all->s[0]));
	i = i->next;
	while (i != all->top[0])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", i->pos, i->id, i->val, i->target, (i->prev - all->s[0]), (i->next - all->s[0]));
		i = i->next;
	}
}
