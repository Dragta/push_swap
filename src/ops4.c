/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/11 20:16:03 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	move_rra(t_compendium *all)
{
	if (!all->top[0] || all->top[0] == all->top[0]->prev)
		return (-1);
	all->top[0] = all->top[0]->prev;
	count_stacks(all);
	return (_RRA);
}

int	move_rrb(t_compendium *all)
{
	if (!all->top[1] || all->top[1] == all->top[1]->prev)
		return (-1);
	all->top[1] = all->top[1]->prev;
	count_stacks(all);
	return (_RRB);
}

int	move_rrr(t_compendium *all)
{
	int	mrra;
	int	mrrb;

	mrra = move_rra(all);
	mrrb = move_rrb(all);
	if (-1 == mrra || -1 == mrrb)
	{
		if (-1 == mrra)
			return (mrrb);
		return (mrra);
	}
	return (_RRR);
}
