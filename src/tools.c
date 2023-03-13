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

void	index(t_list *stk)
{
	t_list	*tmp;

	tmp = *(stk->top);
	tmp->target = 0;
	tmp = tmp->next;
	while(tmp != *(stk->top))
	{
		tmp->target = tmp->prev->target + 1;
		tmp = tmp->next;
	}
}

void	pack(int *data, int n, t_list *stk)
{
	int		i;
	t_list	*new;

	i = 0;
	while (++i < n)
	{
		new = NULL;
		while (data[i] <= stk->prev->datum && stk->datum > stk->prev->datum)
			stk = stk->prev;
		while (data[i] > stk->datum && stk->datum > stk->prev->datum)
			stk = stk->next;
		new = ft_lstnew(data, i);
		if (!new || data[i] == stk->datum)
		{
			write(1, "Error\n", 6);
			free_all(stk);
			break ;
		}
		ft_lstmove_on(new, stk);
	}
	if (new)
		index(stk);

/*	crea nuevo eslabón con primer valor
 *	2º es prev y next del primero
 *	si 3º < ult, comparar con prev hasta que sea >
 *		(y si < cabecera, ult es nueva cabecera)
 *	pero si > ult, compara con next hasta que sea <
 *	si alguno =, write(error) y salir
 *	numerar desde cabecera=0
 */

}

void	process(int *data, int n)
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
}
