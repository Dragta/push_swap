/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/05 20:46:09 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	move_sa(t_compendium *all)
{
	data_atop(all->top[0]->next, all->top[0]);
	if (all->undo)
		all->n_st--;
	else
	{
		all->steps[all->n_st] = _SA;
		all->done[all->n_st] |= 1 << _SA;
		all->cut[all->n_st + 1] = all->cut[all->n_st];
		all->cut[all->n_st + 1] &= all->heir_mask[all->steps[all->n_st]];
		all->cut[all->n_st + 1] |= all->cut_mask[all->steps[all->n_st]];
		all->n_st++;
	}
	return (_SA);
}

int	move_sb(t_compendium *all)
{
	if (!all->undo && ((all->done[all->n_st] & (1 << _SB)) || 
			!all->top[1] || all->top[1]->next == all->top[1]))
		return (-1);
	data_atop(all->top[1]->next, all->top[1]);
	if (all->undo)
		all->n_st--;
	else
	{
		all->steps[all->n_st] = _SB;
		all->done[all->n_st] |= 1 << _SB;
		all->done[all->n_st + 1] |= (1 << _SA) | (1 << _SS);
		all->done[all->n_st + 2] = 0;
		all->n_st++;
	}
	return (_SB);
}

int	move_ss(t_compendium *all)
{
	if (!all->undo && ((all->done[all->n_st] & (1 << _SS)) || 
			!all->top[0] || all->top[0]->next == all->top[0] ||
			!all->top[1] || all->top[1]->next == all->top[1]))
		return (-1);
	data_atop(all->top[0]->next, all->top[0]);
	data_atop(all->top[1]->next, all->top[1]);
	if (all->undo)
		all->n_st--;
	else
	{
		all->steps[all->n_st] = _SB;
		all->done[all->n_st] |= 1 << _SB;
		all->done[all->n_st + 1] |= (1 << _SA) | (1 << _SS);
		all->done[all->n_st + 2] = 0;
		all->n_st++;
	}
	return (_SB);
}

int	move_sb(t_data **stk)
{
	if (stk[0]->top[1] && stk[0]->top[1]->next != stk[0]->top[1])
		data_atop(stk[0]->top[1]->next, stk[0]->top[1]);
}

int	pr_sa(t_data **stk)
{
	move_sa(stk);
	write(1, "sa\n", 3);
}

int	pr_sb(t_data **stk)
{
	move_sb(stk);
	write(1, "sb\n", 3);
}

int	pr_ss(t_data **stk)
{
	move_sa(stk);
	move_sb(stk);
	write(1, "ss\n", 3);
}
