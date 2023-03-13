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

t_list	*ft_lstnew(int *data, int n)
{
	t_list	*newlst;

	newlst = malloc(sizeof(t_list));
	if (!newlst)
		return (NULL);
	newlst->datum = data[n];
	newlst->initial = n;
	newlst->target = -1;
	newlst->top = NULL;
	return (newlst);
}

void	ft_lstmove_on(t_list *node, t_list *stk)
{
	if (*(node->top))
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	else
		node->target = -1;
	*(node->top) = *(stk->top);
	node->prev = stk->prev;
	node->next = stk;
	stk->prev->next = node;
	stk->prev = node;
}
