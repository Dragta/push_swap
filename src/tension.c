/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/05/04 01:41:29 by fsusanna         ###   ########.fr       */
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
		ret = i->next;
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
/*		pos_tns += abs(i->target - i->pos);*/
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
/*	printf("tns, pos_tns: %i, %i\n", tns, pos_tns);*/
	tns += 2 * abs(all->count[1] - all->count_blocked[1] - all->target_B) + 
		pos_tns / (all->count_val - all->count_blocked[0] - all->count_blocked[1]);
	return (tns);
}
/*
int	tot_tension1(t_compendium *all)
{
	int		tns;
	int		pos_tns;
	t_data	*i;
	t_data	*j;

	show_tgts(all);
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
*		pos_tns += abs(i->target - i->pos);*
		if ((i == all->top[0] && j == all->top[1]) ||
			(!i->id && i->prev == j) ||
			(i->id && i->next == j))
			tns += gap(i->target - j->target - 1, all->count_val);
		else
			tns += 1;
		i = j;
		j = after(all, i);
		printf("tns %i, pos_tns %i\n", tns, pos_tns);
	}
	pos_tns += gap(i->target - i->pos, all->count_val);
	printf("tns %i, pos_tns %i\n", tns, pos_tns);
	printf("counts: val %i, blk0 %i, blk1 %i\n", all->count_val, all->count_blocked[0], all->count_blocked[1]);
*	printf("tns, pos_tns: %i, %i\n", tns, pos_tns);*
	tns += 2 * abs(all->count[1] - all->count_blocked[1] - all->target_B) + 
		pos_tns / (all->count_val - all->count_blocked[0] - all->count_blocked[1]);
	printf("Total, tns %i\n", tns);
	return (tns);
}*/

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
		{
			i = all->top[s]->prev;
			p = 0;
			while (i != all->block_btm[s])
			{
				i->pos = all->top[s]->pos - (s + 1) * ++p;
				i = i->prev;
			}
			all->count[s] += p + all->count_blocked[s];
		}
	}
/*	if (all->n_st > 80)
	{
		printf("ct: (n %i, explorados %i)\n", all->n_st, all->positions);
		show_pos(all);
	}*/
}

/*void	index(t_compendium *all)
{
	t_data	*tmp;
	int		i;

	tmp = all->top[0];
	tmp->target = - all->target_B;
	tmp = tmp->next;
	i = 1;
	while(tmp != all->top[0])
	{
		tmp->target = i++ - all->target_B;
		tmp = tmp->next;
	}
	all->s[0].prev = &(all->s[i - 1]);
	all->s[i - 1].next = &(all->s[0]);
	while (--i)
	{
		all->s[i].prev = &(all->s[i - 1]);
		all->s[i - 1].next = &(all->s[i]);
	}
	all->top[0] = all->s;
	count_stacks(all);
}*/