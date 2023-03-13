/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmove_on.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/13 16:54:27 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmove_on(t_list *elem, t_list *stk)
{
	if (elem->top)
	{
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;
	}
	elem->top = stk->top;
	elem->prev = stk->prev;
	elem->next = stk;
	stk->prev->next = elem;
	stk->prev = elem;
}
