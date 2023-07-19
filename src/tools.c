/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/07/05 11:46:06 by fsusanna         ###   ########.fr       */
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

t_data	*find_last (t_compendium *all, int bit)
{
	t_data	*ret;

	ret = all->top[0]->prev;
	while (ret->golden & 1 << (bit + 1))
		ret = ret->prev;
	return (ret);
}

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
	if ((*this)->golden < (*this)->prev->golden && stk)
	{
		move(all, _RRB);
		move(all, _PA);
		move(all, _PA);
	}
	else if (stk)
	{
		move(all, _PA);
		move(all, _RRB);
		move(all, _PA);
	}
	else
		move(all, _RRA);
	this = &(all->top[0]);
	if ((*this)->golden > (*this)->next->golden)
		move(all, _SA);
}

void	process(t_compendium *all, int stk, int ct, int bit)
{
	t_data	**this;
	int		tmp;
	int		ct1;
	int		digit;
	int		sgn;

	if (!ct)
		return ;
	this = &(all->top[stk]);
/*	show_all(all);*/
	sgn = 1;
	if (ct < 0)
		sgn = -1;
	tmp = sgn * ct;
	if (1 == tmp && sgn < 0)
		move(all, _RRA + stk);
	if (1 == tmp && stk)
		move(all, _PA);
	if (1 == tmp)
		return ;
	if (2 == tmp)
	{
		if (ct > 0)
			order_2_plus(all, stk);
		else
			order_2_minus(all, stk);
		return ;
	}
	if (bit < 0)
		return ;
	ct1 = 0;
/*	printf("\n-----------\nstk %i, ct %i, bit %i\n\n", stk, ct, bit);*/
/*	last = this->prev; /find_last(all, bit);*/
	while (tmp--)
	{
		if (sgn < 0)
			move(all, _RRA + stk);
		digit = ((*this)->golden & (1 << bit)) / (1 << bit);
		if (stk == digit || 1 == sgn)
			move(all, _PB + 2 * stk + digit - 4 * stk * digit);
		ct1 += digit;
	}
/*	printf("*\n");*/
	tmp = sgn * ct;
	if (stk || ct1 == all->max[0] || sgn < 0)
		process(all, 0, ct1, bit - 2);
	else
		process(all, 0, -ct1, bit - 2);
	if (!stk || tmp - ct1 == all->max[1] || sgn < 0)
		process(all, 1, tmp - ct1, bit - 1);
	else
		process(all, 1, -(tmp - ct1), bit - 1);
/*	while (all->max[1])
		move(all, _PA);
/	print_steps(all->steps, NEW_LINE);*/
}

void	del_steps(t_compendium *all, int from, int ct)
{
	while(all->steps[from + ct - 1])
	{
		all->steps[from] = all->steps[from + ct];
		from++;
	}
}

void	clean_result(t_compendium *all)
{
	int	i;
	int	nums_in[2];
	int	ct;
	int	stk;

	i = 0;
	nums_in[0] = all->max_val;
	nums_in[1] = 0;

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
	int		bit;

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
	index(all);
	bit = 2;
	while (1 << (bit + 1) < all->max_golden)
		bit++;
	process(all, 0, all->max_val, bit);
	clean_result(all);
	print_steps(all->steps, NEW_LINE);
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
/*		all->base[s] = mean(all, s);
		all->max[s] = all->max_val;*/
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
