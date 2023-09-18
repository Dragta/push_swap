/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 20:43:29 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	abs(int g)
{
	if (g < 0)
		return (-g);
	return (g);
}

int	gap(int g, int max)
{
	g = abs(g);
	if (g > max / 2)
		g = max - g;
	return (g);
}

t_data *after(t_compendium *all, t_data *i)
{
	t_data	*ret;

	if (i == all->top[0])
	{
		ret = all->top[1];
		if (ret && ret == all->block_top[1])
		{
			ret = all->block_btm[1]->next;
			if (ret == all->top[1])
				ret = NULL;
		}
	}
	else if (!i->id)
	{
		ret = i->prev;
		if (ret == all->block_btm[0])
			ret = after(all, all->block_top[0]);
	}
	else if (i == all->top[1]->prev)
		ret = NULL;
	else
	{
		ret = i->next;
		if (ret == all->block_top[1])
			ret = after(all, all->block_btm[1]);
	}
	return (ret);
}

int	tot_tension(t_compendium *all)
{
	int		tns;
	int		pos_tns;
	t_data	*i;
	t_data	*j;

	i = all->top[0];
	if (!i || all->count[0] == all->count_blocked[0])
	{
		i = all->top[1];
		if (i == all->block_top[1])
			i = all->block_btm[1]->next;
	}
	else
	{
		i = i->prev;
		if (i == all->block_btm[0])
			i = all->block_top[0]->prev;
	}
	tns = 0;
	pos_tns = 0;
	j = after(all, i);
	while (j)
	{
		pos_tns += gap(i->target - i->pos, all->count_val);
		if ((i == all->top[0] && j == all->top[1]) ||
			(!i->id && i->prev == j) ||
			(i->id && i->next == j))
			tns += gap(i->target - j->target - 1, all->count_val);
		else
			tns += 1;
		i = j;
		j = after(all, i);
	}
	pos_tns += gap(i->target - i->pos, all->count_val);
	tns += 2 * abs(all->count[1] - all->count_blocked[1]) + 
		pos_tns / (all->count_val - all->count_blocked[0] - all->count_blocked[1]);
	return (tns);
}