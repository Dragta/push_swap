/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean1.c                                           :+:      :+:    :+:   */
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
	while (bot->steps[from + ct - 1])
	{
		bot->steps[from] = bot->steps[from + ct];
		from++;
	}
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

int	reduce(t_crawler *bot)
{
	int		excess;

	if (useless_step(bot))
		del_steps(bot, 1);
	else if (opposite_steps(bot))
		del_steps(bot, 2);
	else if (turnaround(bot))
	{
		excess = turnaround(bot);
		bot->n -= excess - 1;
		del_steps(bot, excess);
		invert(bot);
	}
	else
		return (0);
	return (1);
}

int	clean_steps(char *steps, int vals)
{
	t_crawler	bot;

	bot.steps = steps;
	bot.vals = vals;
	bot.n = 0;
	while (refresh(&bot))
	{
		if (reduce(&bot))
			bot.n = 0;
		else
			bot.n++;
	}
	return (bot.n);
}
