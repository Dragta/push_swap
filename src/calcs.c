/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tension1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/25 00:07:00 by fsusanna         ###   ########.fr       */
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
