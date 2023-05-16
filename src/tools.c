/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/05/16 18:43:21 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

int	abs(int g)
{
	if (g < 0)
		g = -g;
	return (g);
}

int	gap(t_compendium *all, t_data *i)
{
	int	g;
	int	max;

	if (!i)
		return (0);
	g = (i->target - i->prev->target) * (1 - 2 * i->id) - 1;
	max = all->max_val;
	while (g < - max / 2)
		g += max;
	while (g >= max / 2)
		g -= max;
	return (g);
}

int	inter_gap(t_compendium *all, t_data *i)
{
	int	g;
	int	max;

	max = all->max_val;
	if (!i || !all->top[1 - i->id])
		return (max);
	g = (all->base[1 - i->id] + all->max[1 - i->id] - i->target) * (1 - 2 * i->id)  - 1;
	while (g < - max / 2)
		g += max;
	while (g >= max / 2)
		g -= max;
	return (g);
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

void	move(t_compendium *all, int op)
{
	(*(all->ops[op]))(all);
	all->steps[all->n_st] = op;
	init_next_st(all);
	print_1_step(op);
	printf("\n");
/*	printf("%i op %i, a: %i b: %i\n", all->n_st - 1, op, all->max[0], all->max[1]);*/
}

void	process(t_compendium *all)
{
	t_data	**top_[2];
	int		stk;
	int		sense;
	int		ct;
	int		ct_r;
	int		pass;
	int		toler;
	int		init_target;
	int		init_st;

	index(all);
	top_[0] = &(all->top[0]);
	top_[1] = &(all->top[1]);
/*	show_all(all);*/
	all->base[0] = 0;
	all->base[1] = 0;
	stk = 0;
	pass = 1;
	toler = 12;
	sense = 3;
	while (pass < 6 && toler)
	{
		printf("pass %i\n", pass);
		init_target = (*top_[stk])->prev->target;
		init_st = all->n_st;
		if (init_st > 3000)
			break ;
		if (!all->max[1 - stk])
			move(all, _PB - stk);
		ct = 0;
		while ((*top_[stk]) && ct <= 5 * all->max[stk])/* && init_target != (*top_[stk])->target)*/
		{
			all->base[stk] = (*top_[stk])->target - all->max[stk];
			while ((2 * stk - 1) * inter_gap(all, *top_[stk]) < toler &&
					(2 * stk - 1) * inter_gap(all, *top_[stk]) > - toler / 2)
			{
				ct = 0;
				ct_r = 0;
				init_target = (*top_[stk])->prev->target;
				if (!all->max[1 - stk])
					all->base[1 - stk] = (*top_[stk])->target;
/*				else if (inter_gap(all, (*top_[stk])) < 0)
					move(all, _RRB - stk);*/
				move(all, _PB - stk);
			}
			if(*top_[stk])
			{
				if (!ct || ct_r)
					ct_r++;
				ct++;
				move(all, _RA + stk + 3 * (1 - stk));
			}
			if (pass > 2 && ct_r > 4)
			{
				ct_r = 0;
				sense = 3 - sense;
			}
		}
		toler /= 2;
		toler++;
		stk = 1 - stk;
		printf("end pass %i\n", pass);
		pass++;
	}
/*	print_steps(all->steps, NEW_LINE);*/
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
