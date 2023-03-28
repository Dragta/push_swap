/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 02:37:34 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	show_all(t_data **stk, int n)
{
	int		i;

	i = -1;
	printf("id  |val |targ|prev|next\n");
	while (++i <= n)
	{
		printf("%4i|%4i|%4i|%4lu|%4lu\n", stk[i]->id, stk[i]->val, stk[i]->target, (stk[i]->prev - stk[0]), (stk[i]->next - stk[0]));
	}
}

void	show_a(t_data **stk)
{
	t_data	*d;

	d = stk[0]->top[0];
	if (!d)
		return ;
	printf("id  |val |targ|prev|next\n");
	printf("%4i|%4i|%4i|%4lu|%4lu\n", d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
	d = d->next;
	while (d != d->top[0])
	{
		printf("%4i|%4i|%4i|%4lu|%4lu\n", d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
		d = d->next;
	}
}

void	show_b(t_data **stk)
{
	t_data	*d;

	d = stk[0]->top[1];
	if (!d)
		return ;
	printf("id  |val |targ|prev|next\n");
	printf("%4i|%4i|%4i|%4lu|%4lu\n", d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
	d = d->next;
	while (d != d->top[1])
	{
		printf("%4i|%4i|%4i|%4lu|%4lu\n", d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
		d = d->next;
	}
}

void	process(t_data **stk)
{
	printf("top[0]: %4lu\n", (stk[0]->top[0] - stk[0]));
	pr_sa(stk);
	pr_ra(stk);
	pr_pb(stk);
	pr_pb(stk);
	show_a(stk);
	show_b(stk);
}
