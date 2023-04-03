/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/03 11:16:05 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	sense(t_data *tx, t_data *ty, t_data *tz)
{
	int	ret;
	int	x;
	int	y;
	int	z;
	
	x = tx->target;
	y = ty->target;
	z = tz->target;
	ret = 1;
	if (x == y || y == z || z == x)
		ret = 0;
	else if ((x > y && y > z) || (z > x && x > y) || (y > z && z > x))
		ret = -1;
	return (ret);
}

void	process(t_data **stk)
{
	int		ct;
	int		push;
	t_data	**a;
	t_data	**b;

	a = &(stk[0]->top[0]);
	b = &(stk[0]->top[1]);
	ct = 0;
	push = 0;
	while ((trend(*a) < (*a)->max_val || *b) && ct++ < 100 * stk[0]->max_val)
	{
		while (*b && sense(*a, *b, (*a)->next) == 1 &&
			sense(*a, *b, (*b)->prev) == 1)
		{
			push = 0;
			pr_rb(stk);
		}
/*		if (*a)
			pr_pb(stk);*/
		while (!(*b) || *b == (*b)->next || (*a && sense((*b)->next, *b, *a) == 1))
		{
			while (*b && sense(*b, (*b)->prev, *a) == 1)
			{
				push = 0;
				pr_rrb(stk);
			}
			if (push < 1)
			{
				push--;
				pr_pb(stk);
			}
			else
			{
				push = 0;
				pr_rra(stk);
			}
		}

		while (*a && sense(*b, *a, (*b)->next) == -1 &&
			sense(*b, *a, (*a)->prev) == -1)
		{
			push = 0;
			pr_ra(stk);
		}
/*		if (*b)
			pr_pa(stk);*/
		while (!(*a) || *a == (*a)->next || (*b && sense((*a)->next, *a, *b) == -1))
		{
			while (*a && sense(*a, (*a)->prev, *b) == -1)
			{
				push = 0;
				pr_rra(stk);
			}
			if (push > -1)
			{
				push++;
				pr_pa(stk);
			}
			else
			{
				push = 0;
				pr_rrb(stk);
			}
		}

	}
	if (trend(*a) < (*a)->max_val)
		return ;
	while ((*a)->target && (*a)->target < (*a)->max_val / 2)
		pr_rra(stk);
	while ((*a)->target >= (*a)->max_val / 2)
		pr_ra(stk);
}

int	trend(t_data *t)
{
	t_data	*i;
	int		s;
	int		trend;

	if (!t)
		return (0);
	i = t->next;
	if (i == t)
		return (1);
	trend = 2;
/*	if(i->target < t->target && t->target - i->target > t->max_val / 2)*/
	if(i->target < t->target)
		trend = -2;
	if (i->next == t)
		return (trend);
	i = i->next;
	s = sense(t, i->prev, i);
	trend = 3 * s;
	while (i != t && s * trend > 0)
	{
		trend += s;
		i = i->next;
		s = sense(t, i->prev, i);
	}
	return (trend);
}

int	dist(t_data *t)
{
	t_data	*i;
	int		dist;
	int		tmp;

	dist = 0;
	i = t;
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
		if (i == t)
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
/*
void	process(t_data **stk)
{
	int		ct;
	t_data	**a;
	t_data	**b;

	a = &(stk[0]->top[0]);
	b = &(stk[0]->top[1]);
	ct = 0;
	while ((dist(*a) || *b) && ct++ < 10 * stk[0]->max_val)
	{
		while (!(*a) || (*b && ((*b)->target > (*a)->prev->target || 
				(*b)->target - (*a)->target == (*a)->max_val - 1 ||
				 (*b)->target < (*a)->target)))
			pr_pa(stk);
		if ((*a)->target > (*a)->next->target &&
				(*a)->target > (*a)->prev->target && (*a)->next != (*a)->prev)
		{
			if ((*a)->prev->prev->target < (*a)->target)
				pr_pb(stk);
			else
				pr_sa(stk);
		}
		else if (*b && (*b)->target > (*b)->next->target &&
				(*b)->target > (*b)->prev->target)
			pr_sb(stk);
		if (*b && (*b)->target > (*b)->prev->target)
			pr_rrr(stk);
		else
			pr_rra(stk);
	}
}*/
/***********************************************************/
/*void	process(t_data **stk)
{
	int		ct;
	int		i;
	t_data	**a;
	t_data	**b;

	a = &(stk[0]->top[0]);
	b = &(stk[0]->top[1]);
	ct = 0;
	while ((dist(*a) || *b) && ct++ < 10 * stk[0]->max_val)
	{
		if (*a)
		{
			i = trend(*a) + 1;
			while (*a && *b && (*b)->prev->target < (*a)->target && (*b)->target < (*b)->prev->target)
				pr_rrb(stk);
			pr_pb(stk);
			while (i > 1)
			{
				while (--i > -1)
				{
					while (*a && *b && (*b)->prev->target < (*a)->target && (*b)->target < (*b)->prev->target)
						pr_rrb(stk);
					pr_pb(stk);
				}
				i = trend(*a) + 1;
			}
		}
		while (*a && (*a)->target > (*a)->prev->target)
			pr_rra(stk);
		if (*a && (*a)->next == (*a)->prev)
			pr_rra(stk);
		if (*b)
		{
			i = trend(*b) - 1;
			while (*a && *b && (*b)->target < (*a)->prev->target && (*a)->target > (*a)->prev->target)
				pr_rra(stk);
			while (i < -1)
			{
				while (*b && ++i < 1)
				{
					while (*a && *b && (*b)->target < (*a)->prev->target && (*a)->target > (*a)->prev->target)
						pr_rra(stk);
					pr_pa(stk);
				}
				i = trend(*b) - 1;
			}
		}
		while (*b && (*b)->target > (*b)->prev->target)
			pr_rrb(stk);
		if (*b && (*b)->next == (*b)->prev)
			pr_rrb(stk);
		if (*a && (*a)->target > (*a)->next->target)
			pr_rra(stk);*/
	/*	if (*b)
			pr_pa(stk);*/
/*		if ((*a)->target > (*a)->next->target && (*a)->prev->target < (*a)->next->target)
		{
			if ((*a)->target > (*a)->next->next->target)
				pr_pb(stk);
			else
				pr_sa(stk);
		}
		if (*b && (*b)->target < (*b)->next->target && (*b)->target < (*b)->prev->target)
			pr_rb(stk);
		if ((*a)->target && *b && (*b)->target < (*b)->prev->target)
			pr_rrr(stk);
		if ((*a)->target && *b && (*b)->target > (*b)->prev->target)
			pr_rra(stk);
		if (*b && (*b)->target < (*b)->next->target)
			pr_sb(stk);*/
/*	}
}*/
