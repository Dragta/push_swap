/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/27 00:56:56 by fsusanna         ###   ########.fr       */
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

void	move_sa(t_data **stk)
{
	if (stk[0]->head[0] > -1)
		ft_move_data(stk, stk[stk[0]->head[0]]->next, stk[0]->head[0])
}

void	move_sb(t_data **stk)
{
	if (stk[0]->head[1] > -1)
		ft_move_data(stk, stk[stk[0]->head[1]]->next, stk[0]->head[1])
}

void	move_ss(t_data **stk)
{
	move_sa(stk);
	move_sb(stk);
}

void	detach(t_data **stk, int n)
{
	stk[n]->id ^= 1;
	stk[n]->head[stk[n]->id] = n;
	stk[n]->prev = n;
	stk[n]->next = n;
}
void	move_pa(t_data **stk)
{
	if (stk[0]->head[1] > -1)
	{
		if (stk[0]->head[0] > -1)
			ft_move_data(stk, stk[0]->head[1], stk[0]->head[0]);
		else
			detach(stk, stk[0]->head[1]);
	}
}

void	move_pb(t_data **stk)
{
	if (stk[0]->head[0] > -1)
	{
		if (stk[0]->head[1] > -1)
			ft_move_data(stk, stk[0]->head[0], stk[0]->head[1]);
		else
			detach(stk, stk[0]->head[0]);
	}
}

void	move_ra(t_data **stk)
{
	if (stk[0]->head[0] > -1)
		stk[0]->head[0] = stk[stk[0]->head[0]]->next;
}

void	move_rb(t_data **stk)
{
	if (stk[0]->head[1] > -1)
		stk[0]->head[1] = stk[stk[0]->head[1]]->next;
}

void	move_rr(t_data **stk)
{
	move_ra(stk);
	move_rb(stk);
}

void	move_rra(t_data **stk)
{
	if (stk[0]->head[0] > -1)
		stk[0]->head[0] = stk[stk[0]->head[0]]->prev;
}

void	move_rrb(t_data **stk)
{
	if (stk[0]->head[1] > -1)
		stk[0]->head[1] = stk[stk[0]->head[1]]->prev;
}

void	move_rrr(t_data **stk)
{
	move_rra(stk);
	move_rrb(stk);
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
