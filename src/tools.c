/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/04 00:20:44 by fsusanna         ###   ########.fr       */
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

void	assign_ops(void (**ops)(t_data **))
{
	ops[0] = &pr_sa;
	ops[1] = &pr_sb;
	ops[2] = &pr_ss;
	ops[3] = &pr_pa;
	ops[4] = &pr_pb;
	ops[5] = &pr_ra;
	ops[6] = &pr_rb;
	ops[7] = &pr_rr;
	ops[8] = &pr_rra;
	ops[9] = &pr_rrb;
	ops[10] = &pr_rrr;
}

void	process(t_data **stk)
{
	int		ct;
	int		push;
	t_data	**a;
	t_data	**b;
	void	(*ops[11])(t_data **);

	assign_ops(ops);

	a = &(stk[0]->top[0]);
	b = &(stk[0]->top[1]);
	ct = 0;
	push = 0;
}

int	longest(t_data *stk)
{
	t_data	*i;
	int		tmp;
	int		ct;
	int		s;

	s = -1;
	ct = 0;
	while (++s < 2)
	{
		i = stk[0]->top[s];
		if (i)
		{
			tmp = 1;
			while (i->next != stk[0]->top[s])
			{
				tmp++;
				i = i->next;
			}
		}
		if (tmp > ct)
			ct = tmp;
	}
	return (ct);
}

int	gap(int g, int max)
{
	if (g < 0)
		g = -g;
	if (g > max / 2)
		g = max - g;
	return (g);
}

int	inter_tension(t_data **stk)
{
	int		ret;
	t_data	*ia;
	t_data	*ib;
	int		tmp;
	int		ct;

	ret = 0;
	ia = stk[0]->top[0];
	ib = stk[0]->top[1];
	if (!ia || !ib)
		return (0);
	ct = longest(stk);
	tmp = ct / 2;
	while (tmp--)
	{
		ia = ia->prev;
		ib = ib->prev;
	}
	while (ct--)
	{
		ret += gap(ia->target - ib->target, ia->max_val);
		ia = ia->next;
		ib = ib->next;
	}
	return (ret);
}

int	intra_tension(t_data *t)
{
	int		ret;
	t_data	*i;

	ret = gap(t->target - t->next->target, t->max_val);
	i = t->next;
	while (i != t)
	{
		ret +=gap(i->target - i->next->target, i->max_val);
		i = i->next;
	}

	return (ret);
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
	if (n->id)
		i = n->prev;
	else
		i = n->next;
	while (i != n)
	{
		if (n->id)
		{
			i->pos = i->next->pos + 1;
			i = i->prev;
		}
		else
		{
			i->pos = i->prev->pos + 1;
			i = i->next;
		}
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
