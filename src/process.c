/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 20:33:50 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	order_last(t_compendium *all, t_group gr)
{
	set_blocks(all, gr);
	all->min_target = min_target(all, gr);
	start_bt(all);
	all->count_blocked[0] = 0;
	all->count_blocked[1] = 0;
	all->block_top[0] = NULL;
	all->block_top[1] = NULL;
	all->block_btm[0] = NULL;
	all->block_btm[1] = NULL;
}

int	fuse(t_compendium *all, t_group gr)
{
	t_data	*d;
	int		or;
	int		and;
	int		ret;

	d = all->top[gr.stk];
	if (gr.sgn < 0)
		d = d->prev;
	or = d->golden;
	and = d->golden;
	if (gr.sgn > 0)
		d = d->next;
	while (--gr.tmp)
	{
		if (gr.sgn < 0)
			d = d->prev;
		or |= d->golden;
		and &= d->golden;
		if (gr.sgn > 0)
			d = d->next;
	}
	or ^= 0xFFFF;
	ret = and | or;
	return (ret);
}

int	find_last(t_compendium *all, int stk, int bit)
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

int	separate(t_compendium *all, t_group gr)
{
	int		digit;
	int		ret;
	int		fused_val;

	fused_val = fuse(all, gr);
	while (gr.bit > 0 && (fused_val & (1 << gr.bit)))
		gr.bit--;
	ret = 0;
	if (gr.tmp == all->count[gr.stk])
		ret = find_last(all, gr.stk, gr.bit);
	gr.tmp -= ret;
	if (gr.stk)
		ret = 0;
	while (gr.tmp--)
	{
		if (gr.sgn < 0)
			move(all, _RRA + gr.stk);
		digit = (all->top[gr.stk]->golden & (1 << gr.bit)) / (1 << gr.bit);
		if (gr.stk == digit || gr.sgn > 0)
			move(all, _PB + 2 * gr.stk + digit - 4 * gr.stk * digit);
		ret += digit;
	}
	return (ret);
}

void	process(t_compendium *all, t_group gr)
{
	t_group	gr1;

	if (!gr.tmp)
		return ;
	if (gr.tmp <= all->max_bt)
		order_last(all, gr);
	if (gr.tmp <= all->max_bt || gr.bit < 0)
		return ;
	gr1.stk = 0;
	gr1.tmp = separate(all, gr);
	gr1.bit = gr.bit - 2;
	if (gr.stk || gr1.tmp == all->count[0] || gr.sgn < 0)
		gr1.sgn = 1;
	else
		gr1.sgn = -1;
	process(all, gr1);
	gr1.stk = 1;
	gr1.tmp = gr.tmp - gr1.tmp;
	gr1.bit = gr.bit - 1;
	if (!gr.stk || gr1.tmp == all->count[1] || gr.sgn < 0)
		gr1.sgn = 1;
	else
		gr1.sgn = -1;
	process(all, gr1);
}
