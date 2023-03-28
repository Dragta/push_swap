/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/27 19:26:26 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move_ra(t_data **stk)
{
	if (stk[0]->top[0])
		stk[0]->top[0] = stk[0]->top[0]->next;
}

void	move_rb(t_data **stk)
{
	if (stk[0]->top[1])
		stk[0]->top[1] = stk[0]->top[1]->next;
}

void	pr_ra(t_data **stk)
{
	move_ra(stk);
	write(1, "ra\n", 3);
}

void	pr_rb(t_data **stk)
{
	move_rb(stk);
	write(1, "rb\n", 3);
}

void	pr_rr(t_data **stk)
{
	move_ra(stk);
	move_rb(stk);
	write(1, "rr\n", 3);
}
