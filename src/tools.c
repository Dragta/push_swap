/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/05/18 19:36:52 by fsusanna         ###   ########.fr       */
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

int	mod(int g, int max)
{
	while (g < - max / 2)
		g += max;
	while (g >= max / 2)
		g -= max;
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
	return (mod(g, max));
}

int	inter_gap_up(t_compendium *all, t_data *i)
{
	int	g;
	int	max;

	max = all->max_val;
	if (!i || !all->top[1 - i->id])
		return (max);
	g = all->base[1 - i->id] - i->target;
	g += all->max[1 - i->id] * (1 - 2 * i->id);
	return (mod(g, max));
}

int	inter_gap_down(t_compendium *all, t_data *i)
{
	int	g;
	int	max;

	max = all->max_val;
	if (!i || !all->top[1 - i->id])
		return (max);
	g = all->base[1 - i->id] - i->target;
	return (mod(g, max));
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
/*			way = next(all, *top_[stk], toler);*/

int	push_it(t_compendium *all, t_data *i, int toler)
{
	if ((2 * i->id - 1) * inter_gap_up(all, i) < toler &&
			(2 * i->id - 1) * inter_gap_up(all, i) > - toler / 2)
		return (1);
	if ((2 * i->id - 1) * inter_gap_down(all, i) < toler &&
			(2 * i->id - 1) * inter_gap_down(all, i) > - toler / 2)
		return (-1);
	return (0);
}


int	closest(t_compendium *all, t_data *i, int toler)
{
	int	ct;
	int	ct_up;
	int	ct_down;
	t_data	*tmp;

	tmp = i->prev;
	ct_down = 0;
	ct = -1;
	while (++ct < all->max[i->id] / 3)
	{
		if (push_it(all, tmp, toler))
			ct_down++;
		tmp = tmp->prev;
	}
	tmp = i->next;
	ct_up = 0;
	ct = -1;
	while (++ct < 2 * all->max[i->id] / 3)
	{
		if (push_it(all, tmp, toler))
			ct_up++;
		tmp = tmp->next;
	}
	if (ct_up + ct_down == 0)
		return (-1);
	if (ct_up < ct_down)
		return (3);
	return (0);
}

void	process(t_compendium *all)
{
	t_data	**top_[2];
	int		stk;
	int		way;
	int		down;
	int		pass;
	int		toler;
/*	int		init_target;*/
	int		init_st;

	index(all);
	top_[0] = &(all->top[0]);
	top_[1] = &(all->top[1]);
/*	show_all(all);*/
	all->base[0] = 0;
	all->base[1] = 0;
	stk = 0;
	pass = 1;
	toler = 60;
	while (pass < 3 && toler)
	{
/*		printf("pass %i\n", pass);
		init_target = (*top_[stk])->prev->target;*/
		init_st = all->n_st;
		if (init_st > 9000)
			break ;
		if (!all->max[1 - stk])
		{
			all->base[1 - stk] = (*top_[stk])->target;
			move(all, _PB - stk);
		}
		while ((*top_[stk]))/* && ct <= 5 * all->max[stk]) && init_target != (*top_[stk])->target)*/
		{
			all->base[stk] = (*top_[stk])->target - all->max[stk];
			while (push_it(all, *top_[stk], toler))
			{
				down = 0;
				if (push_it(all, *top_[stk], toler) < 0)
					down = 1;
				if (all->max[1 - stk])
					all->base[1 - stk] = (*top_[stk])->target;
				move(all, _PB - stk);
				if (down)
				{
					move(all, _RB - stk);
					all->base[1 - stk] += 2 * stk - 1;
					all->base[1 - stk] = mod(all->base[1 - stk], all->max_val); 
				}
				if (gap(all, (*top_[1 - stk])->next) < 0)
					move(all, _SB - stk);
			}
			way = closest(all, *top_[stk], toler);
			while (way < 0 && all->max[stk] > 5)
			{
				toler = toler * 10 / 9 + 1;
				way = closest(all, *top_[stk], toler);
			}
			if (way < 0)
				break ;
			while (!push_it(all, *top_[stk], toler))
				move(all, _RA + stk + way);
		}
		toler *= 8;
		toler /= 10;
		toler++;
		stk = 1 - stk;
/*		printf("end pass %i\n", pass);*/
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
