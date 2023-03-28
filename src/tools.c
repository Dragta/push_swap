/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 21:24:04 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	show_all(t_data **stk, int n)
{
	int		i;

	i = -1;
	printf("pos |id  |val |targ|prev|next\n");
	while (++i <= n)
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", stk[i]->pos, stk[i]->id, stk[i]->val, stk[i]->target, (stk[i]->prev - stk[0]), (stk[i]->next - stk[0]));
	}
}

void	show_a(t_data **stk)
{
	t_data	*d;

	d = stk[0]->top[0];
	if (!d)
		return ;
	printf("pos |id  |val |targ|prev|next\n");
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
	d = d->next;
	while (d != d->top[0])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
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
	printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
	d = d->next;
	while (d != d->top[1])
	{
		printf("%4i|%4i|%4i|%4i|%4lu|%4lu\n", d->pos, d->id, d->val, d->target, (d->prev - stk[0]), (d->next - stk[0]));
		d = d->next;
	}
}
/*
void	process(t_data **stk)
{
	show_a(stk);
	printf("Dist: %i\n", dist(stk));
	pr_ra(stk);
	while (stk[0]->top[0] != stk[0])
	{
		show_a(stk);
		printf("Dist: %i\n", dist(stk));
		pr_ra(stk);
	}
}*/

void	process(t_data **stk)
{
	int		ct;
	t_data	**a;
	t_data	**b;

	a = &(stk[0]->top[0]);
	b = &(stk[0]->top[1]);
	ct = 0;
	while ((dist(stk) || *b) && ct++ < 10 * stk[0]->max_val)
	{
		while (!(*a) || (*b && ((*b)->target > (*a)->prev->target) &&
				((*b)->target - (*a)->target == (*a)->max_val - 1 ||
				 (*b)->target < (*a)->target)))
			pr_pa(stk);
		if ((*a)->target > (*a)->next->target &&
				(*a)->target > (*a)->prev->target)
		{
			if ((*a)->prev->prev->target < (*a)->target)
				pr_pb(stk);
			else
				pr_sa(stk);
		}
		if (*b && (*b)->target > (*b)->next->target &&
				(*b)->target > (*b)->prev->target)
			pr_sb(stk);
		if (*b && (*b)->target < (*b)->prev->target)
			pr_rrr(stk);
		else
			pr_rra(stk);
	}
}

int	dist(t_data **stk)
{
	t_data	*i;
	int		dist;
	int		tmp;

	dist = 0;
	i = stk[0]->top[0];
	while (i)
	{
		tmp = i->pos - i->target;
		if (tmp < 0)
			tmp *= -1;
		if (tmp > (i->max_val - tmp))
			tmp = i->max_val - tmp;
/*		printf("%i ", tmp);*/
		dist += tmp;
		i = i->next;
		if (i == i->top[0])
			break ;
	}
/*	printf("=> %i.\n", dist);*/
	return (dist);
}

void	set_top(t_data *n)
{
	t_data	*i;

	n->top[n->id] = n;
	n->pos = 0;
	i = n->next;
	while (i != n)
	{
		i->pos = i->prev->pos + 1;
		i = i->next;
	}
}
