/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/07 15:38:53 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pack(int *data, int n, t_list *stack)
{
	int		i;
	t_list	*tmp;
	t_list	*new;

	i = 0;
	tmp = stack;
	while (++i < n)
	{
		if (data[i] < tmp->datum)
		{
			while (data[i] < tmp->prev->datum && tmp != *(tmp->base))
				tmp = tmp->prev;
		}
		else
		{
			while (data[i] > tmp->next->datum && tmp != *(tmp->base))
				tmp = tmp->next;
		}
		new = ft_lstnew(data, i);
		if (!new)
			free_all(stack);
		else
		{
			new->prev = tmp->prev;
			new->next = tmp;
			tmp->prev->next = new;
			tmp->prev = new;
			if (new->datum < tmp->datum)
				*(tmp->base) = new;
		}
	}

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
	stack_a->target = 0;
	pack(data, n, stack_a);
}
