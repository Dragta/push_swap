/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 13:06:20 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*void	print_1_step(int op)
{
	char	*ops;

	if (op < 1 || op > 11)
		return ;
	ops = "xx  sa  sb  ss  pa  pb  ra  rb  rr  rra rrb rrr";
	if (op < 9)
		write(1, ops + 4 * op, 2);
	else
		write(1, ops + 4 * op, 3);
}

void	print_steps(char *ops, int nl)
{
	char	sep;

	sep = ' ';
	if (nl)
		sep = '\n';

	while (*ops)
	{
		print_1_step(*ops);
		write(1, &sep, 1);
		ops++;
	}
}*/

void	settle(t_compendium *all)
{
	while (all->sol[all->n_st])
		move(all, all->sol[all->n_st]);
}

int	settle_part(t_compendium *all)
{
	int	i;

	i = 0;
	while (all->part[i])
		move(all, all->part[i++]);
	return (i);
}

void	backtrack(t_compendium *all)
{
	int		search_depth;
/*	int		und;*/

/*	show_all(all);*/
	all->part[0] = 0;
	all->sol[all->n_st] = 0;
	all->sol_st = all->n_st + LIMIT;
	all->tns[0] = tot_tension(all);
	all->part_tns = all->tns[0];
	search_depth = all->n_st + BACKTRACK_DEPTH;
/*	while (all->tns[0] && all->n_st < LIMIT && (all->n_st || (all->done[0] != ALL_OPS)))*
		write(1, "\n", 1);
		show_tgts(all);
		printf("\n min=%i, mejor tns: %i (%i steps) ", all->min_target, all->part_tns, all->n_st);
		quick_st(all);
		write(1, "\n-_-\n", 5);
	printf("(tns0 %i)", all->tns[0]);
	show_tgts(all);*/
	if (!all->tns[0])
		return ;
	while (!all->sol[all->n_st] && all->tolerance < 10000)
	{
		all->tolerance *= 2;
		all->done[all->n_st] = 0;
		all->cut[all->n_st] = 0;
		fan(all, search_depth);
		all->tns[0] = tot_tension(all);
	}
/*	if (!all->sol[0])
	{
		und = settle_part(all);
		printf("part %i\n", und);
		show_tgts(all);
	}*/
	settle(all);
/*	if (all->part[0])
		all->part[0] = 0;
		else
		printf("%i\n", all->tns[0]);*
	if (!all->n_st && all->done[0] == ALL_OPS)
		up_tolerance(all);*/
/*	printf("Positions: %i\n", all->positions);
	print_steps(all->sol, NEW_LINE);*/
}

/*uso:
 *				(*ops[x])(stk)
 */
void	start_bt(t_compendium *all)
{
/*	const int	c_m[] = {0, 14, 14, 14, 32, 16, 2688, 3136, 3584, 1344, 896, 448};
	const int	h_m[] = {0, 3470, 2894, 14, 0, 0,
		3972, 3906, 3584, 3460, 3394, 448};

	all->cut_mask = (int *)c_m;
	all->heir_mask = (int *)h_m;*/
	all->done[0] = 0;
	all->cut[0] = 0;
	all->tolerance = TOLERANCE;
	count_stacks(all);
	backtrack(all);
}