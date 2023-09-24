/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/25 00:13:26 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	data_atop(t_compendium *all, t_data *mv, int stk)
{
	if (!mv || all->top[stk] == mv || (mv->id != stk && all->top[mv->id] != mv))
		return (-1);
	mv->prev->next = mv->next;
	mv->next->prev = mv->prev;
	if (mv->id != stk)
	{
		all->top[mv->id] = NULL;
		if (mv->next != mv)
			all->top[mv->id] = mv->next;
	}
	mv->id = stk;
	if (!all->top[stk])
	{
		mv->prev = mv;
		mv->next = mv;
	}
	else
	{
		mv->prev = all->top[stk]->prev;
		mv->next = all->top[stk];
		all->top[stk]->prev = mv;
		mv->prev->next = mv;
	}
	all->top[stk] = mv;
	return (0);
}

int	move_pa(t_compendium *all)
{
	if (!all->top[1] || data_atop(all, all->top[1], 0))
		return (-1);
	return (_PA);
}

int	move_pb(t_compendium *all)
{
	if (!all->top[0] || data_atop(all, all->top[0], 1))
		return (-1);
	return (_PB);
}
