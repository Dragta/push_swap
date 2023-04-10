/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/10 02:14:01 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	move_sa(t_compendium *all)
{
	data_atop(all->top[0]->next, all->top[0]);
	return (_SA);
}

int	move_sb(t_compendium *all)
{
	data_atop(all->top[1]->next, all->top[1]);
	return (_SB);
}

int	move_ss(t_compendium *all)
{
	data_atop(all->top[0]->next, all->top[0]);
	data_atop(all->top[1]->next, all->top[1]);
	return (_SS);
}
