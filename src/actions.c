/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 20:54:23 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move(t_compendium *all, int op)
{
	int	op_done;

	op_done = (*(all->ops[op]))(all);
	if (op_done > 0)
	{
		all->steps[all->n_st] = op_done;
		all->steps[all->n_st + 1] = 0;
		all->done[all->n_st + 1] = 0;
		all->cut[all->n_st + 1] = all->cut[all->n_st];
		all->cut[all->n_st + 1] &= all->heir_mask[(int)all->steps[all->n_st]];
		all->cut[all->n_st + 1] |= all->cut_mask[(int)all->steps[all->n_st]];
		all->n_st++;
		count_stacks(all);
	}
}

void	settle(t_compendium *all)
{
	while (all->sol[all->n_st])
		move(all, all->sol[all->n_st]);
}

void	count_blk(t_compendium *all, int s)
{
	t_data	*i;
	int		p;

	i = all->top[s]->prev;
	p = 0;
	while (i != all->block_btm[s])
	{
		i->pos = all->top[s]->pos - (s + 1) * ++p;
		i = i->prev;
	}
	all->count[s] += p + all->count_blocked[s];
}

void	count_stacks(t_compendium *all)
{
	t_data	*i;
	int		p;
	int		s;

	s = -1;
	while (++s < 2)
	{
		all->count[s] = 0;
		i = all->top[s];
		if (!i)
			continue ;
		i->pos = all->min_target - s;
		p = 0;
		while (i != all->block_top[s])
		{
			i->pos = all->top[s]->pos + s + (1 - 2 * s) * (p++ + s);
			i = i->next;
			if (i == all->top[s])
				break ;
		}
		all->count[s] = p;
		if (all->count_blocked[s])
			count_blk(all, s);
	}
}

int	undo(t_compendium *all, int n)
{
	int	op;

	n++;
	while (--n > 0)
	{
		if (!all->n_st)
			n = -1;
		else
		{
			op = all->revert[(int)all->steps[all->n_st - 1]];
			op = (*(all->ops[op]))(all);
			all->steps[all->n_st - 1] = 0;
			all->n_st--;
		}
	}
	count_stacks(all);
	all->tns[0] = tot_tension(all);
	if (exclude(all) == ALL_OPS)
		all->tns[0] = -1;
	return (n);
}

void	save_part(t_compendium *all, int bt_z)
{
	int	i;

	if (all->tns[0] && all->tns[0] > all->part_tns)
		return ;
	all->part_tns = all->tns[0];
	i = all->n_st;
	all->part[i] = 0;
	while (--i >= bt_z)
		all->part[i] = all->steps[i];
	if (!all->part_tns)
	{
		i = all->n_st + 1;
		while (--i >= 0)
			all->sol[i] = all->steps[i];
		all->sol_st = all->n_st;
	}
}
