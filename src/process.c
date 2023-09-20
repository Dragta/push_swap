/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 20:33:50 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	order_last(t_compendium *all, int stk, int tmp, int sgn)
{
/*	printf("order_last stk %i tmp %i sgn %i\n", stk, tmp, sgn);*/
	set_blocks(all, stk, tmp, sgn);
	all->min_target = min_target(all, stk, tmp, sgn);
	start_bt(all);
	all->count_blocked[0] = 0;
	all->count_blocked[1] = 0;
	all->block_top[0] = NULL;
	all->block_top[1] = NULL;
	all->block_btm[0] = NULL;
	all->block_btm[1] = NULL;
}

int	fuse(t_compendium *all, int stk, int tmp, int sgn)
{
	t_data	*d;
	int		or;
	int		and;
	int		ret;

	d = all->top[stk];
	if (sgn < 0)
		d = d->prev;
	or = d->golden;
	and = d->golden;
	if (sgn > 0)
		d = d->next;
	while (--tmp)
	{
		if (sgn < 0)
			d = d->prev;
		or |= d->golden;
		and &= d->golden;
		if (sgn > 0)
			d = d->next;
	}
	or ^= 0xFFFF;
	ret = and | or;
	return (ret);
}

int	find_last (t_compendium *all, int stk, int bit)
{
	t_data	*last;
	int		ret;

	last = all->top[stk]->prev;
	ret = 0;
	while ((last->golden & (1 << bit)) != (1 << bit) * stk)
	{
		last = last->prev;
		ret++;
	}
	return (ret);
}

int	separate(t_compendium *all, int stk, int tmp, int sgn, int bit)
{
	int		digit;
	int		ret;
	int		fused_val;

/*	printf("separate stk %i tmp %i sgn %i bit %i\n", stk, tmp, sgn, bit);*/
	fused_val = fuse(all, stk, tmp, sgn);
	while (bit > 0 && (fused_val & (1 << bit)))
		bit--;
	ret = 0;
	if (tmp == all->count[stk])
		ret = find_last(all, stk, bit);
	tmp -= ret;
	if (stk)
		ret = 0;
	while (tmp--)
	{
		if (sgn < 0)
			move(all, _RRA + stk);
		digit = (all->top[stk]->golden & (1 << bit)) / (1 << bit);
		if (stk == digit || sgn > 0)
			move(all, _PB + 2 * stk + digit - 4 * stk * digit);
		ret += digit;
	}
	return (ret);
}

void	process(t_compendium *all, int stk, int ct, int bit)
{
	int		tmp;
	int		ct1;
	int		sgn;

	if (!ct)
		return ;
	sgn = 1;
	if (ct < 0)
		sgn = -1;
	tmp = sgn * ct;
	if (tmp <= all->max_bt) /*<5 => backtracking*/
		order_last(all, stk, tmp, sgn);
	if (tmp <= all->max_bt || bit < 0)
		return ;
	ct1 = separate(all, stk, tmp, sgn, bit);
	if (stk || ct1 == all->count[0] || sgn < 0)
		process(all, 0, ct1, bit - 2);
	else
		process(all, 0, -ct1, bit - 2);
	if (!stk || tmp - ct1 == all->count[1] || sgn < 0)
		process(all, 1, tmp - ct1, bit - 1);
	else
		process(all, 1, -(tmp - ct1), bit - 1);
}