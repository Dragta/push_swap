/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 01:28:27 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move_sa(t_data **stk)
{
	if (stk[0]->top[0] && stk[0]->top[0]->next != stk[0]->top[0])
		data_atop(stk[0]->top[0]->next, stk[0]->top[0]);
}

void	move_sb(t_data **stk)
{
	if (stk[0]->top[1] && stk[0]->top[1]->next != stk[0]->top[1])
		data_atop(stk[0]->top[1]->next, stk[0]->top[1]);
}

void	pr_sa(t_data **stk)
{
	move_sa(stk);
	write(1, "sa\n", 3);
}

void	pr_sb(t_data **stk)
{
	move_sb(stk);
	write(1, "sb\n", 3);
}

void	pr_ss(t_data **stk)
{
	move_sa(stk);
	move_sb(stk);
	write(1, "ss\n", 3);
}
