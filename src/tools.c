/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/07/30 20:32:18 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_1_step(int op)
{
	char	*ops;

	if (op < 1 || op > 11)
		return ;
	ops = "xx  sa  sb  ss  pa  pb  ra  rb  rr  rra rrb rrr";
	if (op < 8)
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
	if (_PB == op_done)
	{
		all->count[0]--;
		all->count[1]++;
	}
	if (_PA == op_done)
	{
		all->count[0]++;
		all->count[1]--;
	}
	all->steps[all->n_st] = op;
	all->n_st++;
	all->steps[all->n_st] = 0;
/*	print_1_step(op);
	printf("\n");*/
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

int	separate(t_compendium *all, int stk, int tmp, int sgn, int bit)
{
	int	digit;
	int	ret;

	ret = 0;
	while (tmp--)
	{
		if (sgn < 0)
			move(all, _RRA + stk);
		digit = (all->top[stk]->golden & (1 << bit)) / (1 << bit);
		if (stk == digit || 1 == sgn)
			move(all, _PB + 2 * stk + digit - 4 * stk * digit);
		ret += digit;
	}
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
	if (tmp < 3)
		order_last(all, stk, tmp, sgn);
	if (tmp < 3 || bit < 0)
		return ;
	ct1 = separate(all, stk, tmp, sgn, bit);
	tmp = sgn * ct;
	if (stk || ct1 == all->count[0] || sgn < 0)
		process(all, 0, ct1, bit - 2);
	else
		process(all, 0, -ct1, bit - 2);
	if (!stk || tmp - ct1 == all->count[1] || sgn < 0)
		process(all, 1, tmp - ct1, bit - 1);
	else
		process(all, 1, -(tmp - ct1), bit - 1);
}

void	del_steps(t_crawler *bot, int ct)
{
	int	from;

	if (ct < 1)
		return ;
	from = bot->n;
/*	printf("\n________________\ndel from %i, %i steps\n", from, ct);*/
	while(bot->steps[from + ct - 1])
	{
		bot->steps[from] = bot->steps[from + ct];
		from++;
	}
/*	print_steps(bot->steps, NEW_LINE);*/
}

int	refresh(t_crawler *bot)
{
	int	step;
	int 	i;

	i = 0;
	bot->repeated_op = 0;
	bot->times = 0;
	bot->in_stack_A = bot->vals;
	step = bot->steps[i];
	while (step && i <= bot->n)
	{
		if (CHECK_TURNAROUND & (1 << step) && step != bot->repeated_op)
		{
			bot->repeated_op = step;
			bot->times = 1;
		}
		else if (step == bot->repeated_op)
			bot->times++;
		else
		{
			bot->repeated_op = 0;
			bot->times = 0;
		}
		if (_PB == step)
			bot->in_stack_A--;
		if (_PA == step)
			bot->in_stack_A++;
		i++;
		step = bot->steps[i];
	}
	return (step);
}

int	useless_step(t_crawler *bot)
{
	int	step;
	int	ret;

	ret = 0;
	step = bot->steps[bot->n];
	if (-1 == bot->in_stack_A ||
			bot->vals + 1 == bot->in_stack_A ||
			((bot->in_stack_A < 2) && (CLEAN_1A & (1 << step))) ||
			((bot->vals - bot->in_stack_A < 2) &&
			(CLEAN_1B & (1 << step))))
		ret = 1;
/*	printf("useless: %i; ", ret);*/
	return (ret);
}

int	opposite_steps(t_crawler *bot)
{
	int	step;
	int	step1;
	int	ret;

	ret = 0;
	step = bot->steps[bot->n];
	step1 = bot->steps[bot->n + 1];
	if (((2 == bot->in_stack_A) && (CLEAN_2A & (1 << step)) &&
			(CLEAN_2A & (1 << step1))) ||
			((2 == bot->vals - bot->in_stack_A) && (CLEAN_2B & (1 << step)) &&
			(CLEAN_2B & (1 << step1))) ||
			(((1 << step) | (1 << step1)) == 
			((1 << _PA) | (1 << _PB))) ||
			(((1 << step) | (1 << step1)) == 
			((1 << _RA) | (1 << _RRA))) ||
			(((1 << step) | (1 << step1)) == 
			((1 << _RB) | (1 << _RRB))))
		ret = 2;
/*	printf("opposite: %i; ", ret);*/
	return (ret);
}

void	invert(t_crawler *bot)
{
	bot->n--;
	while (bot->n >= 0 && bot->steps[bot->n] == bot->repeated_op)
	{
		if (bot->steps[bot->n] < _RR)
			bot->steps[bot->n] += 3;
		else
			bot->steps[bot->n] -= 3;
		bot->n--;
	}
}

int	turnaround(t_crawler *bot)
{
	int	dif;
	int	ret;

	ret = 0;
	dif = 0;
/*	if (bot->repeated_op && (bot->repeated_op != bot->steps[bot->n + 1] ||
		(bot->repeated_op % 3 == 0 && bot->times == bot->in_stack_A) ||
		(bot->repeated_op % 3 == 1 && bot->times == (bot->vals - bot->in_stack_A))))

	{
		printf("tot %i, A%i, times %i\n", bot->vals, bot->in_stack_A, bot->times);*/
	if (_RA == bot->repeated_op || _RRA == bot->repeated_op)
		dif = bot->in_stack_A - bot->times;
	if (_RB == bot->repeated_op || _RRB == bot->repeated_op)
		dif = bot->vals - bot->in_stack_A - bot->times;
	if (bot->times > dif &&
		(bot->repeated_op != bot->steps[bot->n + 1] || !dif))
		ret = bot->times - dif;
/*	printf("turnaround: (dif %i) %i\n", dif, ret);*/
	return (ret);
}

int	clean_steps(char *steps, int vals)
{
	t_crawler	bot;
	int		excess;

	bot.steps = steps;
	bot.vals = vals;
	bot.n = 0;
	while (refresh(&bot))
	{
/*		printf("n: %i: ", bot.n);*/
		if (useless_step(&bot))
			del_steps(&bot, 1);
		else if (opposite_steps(&bot))
			del_steps(&bot, 2);
		else if(turnaround(&bot))
		{
			excess = turnaround(&bot);
			bot.n -= excess - 1;
			del_steps(&bot, excess);
			invert(&bot);
		}
		else
		{
			bot.n++;
			continue ;
		}
		bot.n = 0;
	}
	return (bot.n);
}
/*
void	clean_result(t_compendium *all)
{
	int	i;
	int	_in[2];
	int	step;
	int	step1;

	i = 0;
	_in[0] = all->count_val;
	_in[1] = 0;
*	printf("in0: %i; in1: %i.\n", _in[0], _in[1]);*
	step = all->steps[i];
	step1 = all->steps[i + 1];
	while (step)
	{
*		print_1_step(step);
		if (step < 9)
			printf(" ");
		printf(" in0: %i; in1: %i.\n", _in[0], _in[1]);*
		if (((_in[0] < 2) && (CLEAN_1A & (1 << step))) ||
				(!_in[0] && (_PB == step)) ||
				((_in[1] < 2) && (CLEAN_1B & (1 << step))) ||
				(!_in[1] && (_PA == step)))
			del_steps(all, i, 1);
		else if (((2 == _in[0]) && (CLEAN_2A & (1 << step)) &&
				(CLEAN_2A & (1 << step1))) ||
				((2 == _in[1]) && (CLEAN_2B & (1 << step)) &&
				(CLEAN_2B & (1 << step1))) ||
				(((1 << step) | (1 << step1)) == 
				((1 << _PA) | (1 << _PB))) ||
				(((1 << step) | (1 << step1)) == 
				((1 << _RA) | (1 << _RRA))) ||
				(((1 << step) | (1 << step1)) == 
				((1 << _RB) | (1 << _RRB))))
		{
			del_steps(all, i, 2);
			if (i)
			{
				i--;
				if (_PB == all->steps[i])
				{
					_in[0]++;
					_in[1]--;
				}
				if (_PA == all->steps[i])
				{
					_in[0]--;
					_in[1]++;
				}
			}
		}
		else if (_PB == step)
		{
			_in[0]--;
			_in[1]++;
			i++;
		}
		else if (_PA == step)
		{
			_in[0]++;
			_in[1]--;
			i++;
		}
		else
			i++;
		step = all->steps[i];
		step1 = all->steps[i + 1];
	}
}*/


/*uso:
 *				(*ops[x])(stk)
 */
void	start(t_compendium *all)
{
	int		bit;

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
	index(all);
	bit = 2;
	while (1 << (bit + 1) <= all->count_golden)
		bit++;
	process(all, 0, all->count_val, bit);
/*	clean_steps(all);
	print_steps(all->steps, NEW_LINE);*/
	all->n_st = clean_steps(all->steps, all->count_val);
	print_steps(all->steps, NEW_LINE);
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
/*
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
}*/
