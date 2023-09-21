/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/07/30 20:32:18 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	useless_step(t_crawler *bot)
{
	int	step;
	int	ret;

	ret = 0;
	step = bot->steps[bot->n];
	if (-1 == bot->in_stack_a
		|| bot->vals + 1 == bot->in_stack_a
		|| ((bot->in_stack_a < 2) && (CLEAN_1A & (1 << step)))
		|| ((bot->vals - bot->in_stack_a < 2)
			&& (CLEAN_1B & (1 << step))))
		ret = 1;
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
	if (((2 == bot->in_stack_a) && (CLEAN_2A & (1 << step))
			&& (CLEAN_2A & (1 << step1)))
		|| ((2 == bot->vals - bot->in_stack_a) && (CLEAN_2B & (1 << step))
			&& (CLEAN_2B & (1 << step1)))
		|| (((1 << step) | (1 << step1))
			== ((1 << _PA) | (1 << _PB)))
		|| (((1 << step) | (1 << step1))
			== ((1 << _RA) | (1 << _RRA)))
		|| (((1 << step) | (1 << step1))
			== ((1 << _RB) | (1 << _RRB))))
		ret = 2;
	return (ret);
}

int	turnaround(t_crawler *bot)
{
	int	dif;
	int	ret;

	ret = 0;
	dif = 0;
	if (_RA == bot->repeated_op || _RRA == bot->repeated_op)
		dif = bot->in_stack_a - bot->times;
	if (_RB == bot->repeated_op || _RRB == bot->repeated_op)
		dif = bot->vals - bot->in_stack_a - bot->times;
	if (bot->times > dif
		&& (bot->repeated_op != bot->steps[bot->n + 1] || !dif))
		ret = bot->times - dif;
	return (ret);
}

void	refresh2(t_crawler *bot, int step)
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
		bot->in_stack_a--;
	if (_PA == step)
		bot->in_stack_a++;
}

int	refresh(t_crawler *bot)
{
	int	step;
	int	i;

	i = 0;
	bot->repeated_op = 0;
	bot->times = 0;
	bot->in_stack_a = bot->vals;
	step = bot->steps[i];
	while (step && i <= bot->n)
	{
		refresh2(bot, step);
		i++;
		step = bot->steps[i];
	}
	return (step);
}
