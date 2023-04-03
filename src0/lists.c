/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/13 23:34:58 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_move_data(t_data *stk, int mv, int on)
{
	if (stk[mv].id > -1)
	{
		stk[stk[mv].next].prev = stk[mv].prev;
		stk[stk[mv].prev].next = stk[mv].next;
	}
	stk[mv].id = stk[on].id;
	stk[mv].prev = stk[on].prev;
	stk[mv].next = on;
	stk[on].prev = mv;
	stk[stk[mv].prev].next = mv;
}
