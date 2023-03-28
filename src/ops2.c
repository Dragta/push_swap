/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 01:28:07 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	data_atop(t_data *mv, t_data *on)
{
	if (mv->prev != mv)
	{
		if (mv->prev != on)
			mv->top[mv->id] = mv->next;
		mv->prev->next = mv->next;
		mv->next->prev = mv->prev;
	}
	else
		mv->top[mv->id] = NULL;
	if (!on)
	{
		mv->id = 1 - mv->id;
		mv->prev = mv;
		mv->next = mv;
	}
	else
	{
		mv->id = on->id;
		mv->prev = on->prev;
		mv->next = on;
		on->prev = mv;
		mv->prev->next = mv;
	}
	mv->top[mv->id] = mv;
}

void	pr_pa(t_data **stk)
{
	if (stk[0]->top[1])
		data_atop(stk[0]->top[1], stk[0]->top[0]);
	write(1, "pa\n", 3);
}

void	pr_pb(t_data **stk)
{
	if (stk[0]->top[0])
		data_atop(stk[0]->top[0], stk[0]->top[1]);
	write(1, "pb\n", 3);
}
