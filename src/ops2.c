/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/10 20:03:21 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	data_atop(t_compendium *all, t_data *mv, int stack)
{
	if (!mv || all->top[stack] == mv || (mv->id != stack && all->top[mv->id] != mv))
		return (-1);
	mv->prev->next = mv->next;
	mv->next->prev = mv->prev;
	if (mv->id != stack)
	{
		all->top[mv->id] = NULL;
		if (mv->next != mv)
			all->top[mv->id] = mv->next;
	}
	mv->id = stack;
	if (!all->top[stack])
	{
		mv->prev = mv;
		mv->next = mv;
	}
	else
	{
		mv->prev = all->top[stack]->prev;
		mv->next = all->top[stack];
		all->top[stack]->prev = mv;
		mv->prev->next = mv;
	}
	all->top[stack] = mv;
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
