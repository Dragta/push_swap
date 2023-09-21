/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 20:34:11 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	min_target(t_compendium *all, t_group gr)
{
	t_data	*i;
	int		ret;

	i = all->top[gr.stk];
	if (gr.sgn < 0)
		i = i->prev;
	ret = i->target;
	while (--gr.tmp)
	{
		if (gr.sgn < 0)
			i = i->prev;
		else
			i = i->next;
		if (i->target < ret)
			ret = i->target;
	}
	return (ret);
}

void	set_blocks(t_compendium *all, t_group gr)
{
	int	t;

	t = gr.tmp;
	all->count_blocked[1 - gr.stk] = all->count[1 - gr.stk];
	all->block_top[1 - gr.stk] = all->top[1 - gr.stk];
	if (all->top[1 - gr.stk])
	{
		all->block_btm[1 - gr.stk] = all->top[1 - gr.stk]->prev;
	}
	else
		all->block_btm[1 - gr.stk] = NULL;
	all->count_blocked[gr.stk] = all->count[gr.stk] - gr.tmp;
	if (all->count_blocked[gr.stk])
	{
		all->block_top[gr.stk] = all->top[gr.stk];
		all->block_btm[gr.stk] = all->top[gr.stk]->prev;
		while (gr.sgn < 0 && t--)
			all->block_btm[gr.stk] = all->block_btm[gr.stk]->prev;
		while (gr.sgn > 0 && t--)
			all->block_top[gr.stk] = all->block_top[gr.stk]->next;
	}
}

void	fan(t_compendium *all, int search_depth)
{
	int	min_tns;
	int	bt_z;

	if (search_depth >= all->sol_st)
		search_depth = all->sol_st - 1;
	min_tns = all->tns[0];
	bt_z = all->n_st;
	while (all->n_st < search_depth && (bt_z < all->n_st || all->tns[0] > -1))
	{
		all->tns[0] = apply_min(all);
		if (all->tns[0] > -1 && all->tns[0] <= min_tns + 1)
		{
			if (all->tns[0] < min_tns)
				min_tns = all->tns[0];
			if (!all->tns[0])
				search_depth = all->n_st - 1;
			save_part(all, bt_z);
			if (all->part_tns > 0 && all->n_st > search_depth - 2)
				fan(all, all->n_st + BACKTRACK_DEPTH);
		}
		while (all->n_st > bt_z
			&& (all->n_st >= search_depth || all->tns[0] < 0))
			undo(all, 1);
	}
}

void	backtrack(t_compendium *all)
{
	int		search_depth;

	all->part[0] = 0;
	all->sol[all->n_st] = 0;
	all->sol_st = all->n_st + LIMIT;
	all->tns[0] = tot_tension(all);
	all->part_tns = all->tns[0];
	search_depth = all->n_st + BACKTRACK_DEPTH;
	if (!all->tns[0])
		return ;
	while (!all->sol[all->n_st] && all->tolerance < 10000)
	{
		if (all->tolerance > TOLERANCE)
			printf("tol*2 %i\n", all->tolerance * 2);
		all->tolerance *= 2;
		all->done[all->n_st] = 0;
		all->cut[all->n_st] = 0;
		fan(all, search_depth);
		all->tns[0] = tot_tension(all);
	}
	settle(all);
}

void	start_bt(t_compendium *all)
{
	all->done[0] = 0;
	all->cut[0] = 0;
	all->tolerance = TOLERANCE;
	count_stacks(all);
	backtrack(all);
}
