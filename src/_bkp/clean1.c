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
