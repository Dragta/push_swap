/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/13 18:09:21 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	process(t_data **stk, int n)
{
	int		i;

	i = -1;
	printf("id  |val |targ|prev|next\n");
	while (++i < n)
	{
		printf("%4i|%4i|%4i|%4i|%4i\n", stk[i]->id, stk[i]->val, stk[i]->target, stk[i]->prev, stk[i]->next);
	}
}

void	move_ra(t_data **stk)
{
	
}


/*
void	process(t_data *stk, int n)
{
	int		i;
	int		max;
	int		min;
	t_list	*stack_a;

	stack_a = ft_lstnew(data, 0);
	if (!stack_a)
	{
		write(1, "Error\n", 6);
		return ;
	}
	stack_a->target = 0;
	pack(data, n, stack_a);
}*/
