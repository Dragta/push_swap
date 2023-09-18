/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/10 18:54:53 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	move_sa(t_compendium *all)
{
	if (!all->top[0] || all->top[0]->next == all->top[0])
		return (-1);
	data_atop(all, all->top[0]->next, 0);
	return (_SA);
}

int	move_sb(t_compendium *all)
{
	if (!all->top[1] || all->top[1]->next == all->top[1])
		return (-1);
	data_atop(all, all->top[1]->next, 1);
	return (_SB);
}

int	move_ss(t_compendium *all)
{
	int	msa;
	int	msb;

	msa = move_sa(all);
	msb = move_sb(all);
	if (-1 == msa || -1 == msb)
	{
		if (-1 == msa)
			return (msb);
		return (msa);
	}
	return (_SS);
}
