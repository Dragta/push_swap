/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
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
