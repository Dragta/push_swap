/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/11 20:17:02 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	move_ra(t_compendium *all)
{
	if (!all->top[0] || all->top[0] == all->top[0]->next)
		return (-1);
	all->top[0] = all->top[0]->next;
	count_stacks(all);
	return (_RA);
}

int	move_rb(t_compendium *all)
{
	if (!all->top[1] || all->top[1] == all->top[1]->next)
		return (-1);
	all->top[1] = all->top[1]->next;
	count_stacks(all);
	return (_RB);
}

int	move_rr(t_compendium *all)
{
	int	mra;
	int	mrb;

	mra = move_ra(all);
	mrb = move_rb(all);
	if (-1 == mra || -1 == mrb)
	{
		if (-1 == mra)
			return (mrb);
		return (mra);
	}
	return (_RR);
}
