/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 19:46:09 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move_rra(t_data **stk)
{
	if (stk[0]->top[0])
		set_top(stk[0]->top[0]->prev);
}

void	move_rrb(t_data **stk)
{
	if (stk[0]->top[1])
		set_top(stk[0]->top[1]->prev);
}

void	pr_rra(t_data **stk)
{
	move_rra(stk);
	write(1, "rra\n", 4);
}

void	pr_rrb(t_data **stk)
{
	move_rrb(stk);
	write(1, "rrb\n", 4);
}

void	pr_rrr(t_data **stk)
{
	move_rra(stk);
	move_rrb(stk);
	write(1, "rrr\n", 4);
}
