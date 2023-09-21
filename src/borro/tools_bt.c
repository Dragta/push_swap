#include "../push_swap.h"

int	min_step(t_compendium *all, int *op)
{
	int	min_tns;
	int	low;

	min_tns = -1;
	low = 12;
	while (--low)
	{
		if (all->tns[low] > -1 && (all->tns[low] < min_tns || min_tns < 0))
		{
			min_tns = all->tns[low];
			*op = low;
		}
	}
	return (min_tns);
}

int	apply_min(t_compendium *all)
{
	int	do_op;
	int	ret_tns;

	ret_tns = -1;
	do_op = 0;
	ret_tns = min_step(all, &do_op);
	if (do_op)
	{
		all->done[all->n_st] |= 1 << do_op;
		all->tns[do_op] = -1;
		all->positions++;
		move(all, do_op);
/*		printf("\n%i: ", all->positions);
		quick_st(all);*/
	}
	return (ret_tns);
}

int	exclude(t_compendium *all)
{
	int	ret;

	ret = 0;
	if (!(all->count[0] - all->count_blocked[0]))
		ret |= NOT_0A;
	if (all->top[0] == all->block_top[0])
		ret |= NOT_0TOP_A;
	if (!(all->count[1] - all->count_blocked[1]))
		ret |= NOT_0B;
	if (all->top[1] == all->block_top[1])
		ret |= NOT_0TOP_B;
	if ((all->count[0] - all->count_blocked[0]) < 2)
		ret |= NOT_1A;
	if (all->top[0] && all->top[0]->next == all->block_top[0])
		ret |= NOT_1TOP_A;
	if ((all->count[1] - all->count_blocked[1]) < 2)
		ret |= NOT_1B;
	if (all->top[1] && all->top[1]->next == all->block_top[1])
		ret |= NOT_1TOP_B;
	if ((all->count[0] - all->count_blocked[0]) < 3)
		ret |= NOT_2A;
	if ((all->count[1] - all->count_blocked[1]) < 3)
		ret |= NOT_2B;
	if (all->top[0] && all->top[0]->prev == all->block_btm[0])
		ret |= NOT_0BTM_A;
	if (all->top[1] && all->top[1]->prev == all->block_btm[1])
		ret |= NOT_0BTM_B;
	ret |= all->done[all->n_st];
	ret |= all->cut[all->n_st];
	return (ret);
}

int	undo(t_compendium *all, int n)
{
	int	op;

	n++;
	while (--n)
	{
		if (!all->n_st)
		{
			n = -1;
			break ;
		}
		op = all->revert[(int)all->steps[all->n_st - 1]];
		all->steps[all->n_st - 1] = 0;
		all->n_st--;
	}
	count_stacks(all);
	all->tns[0] = tot_tension(all);
	if (exclude(all) == ALL_OPS)
		all->tns[0] = -1;
	return (n);
}

void	eval_moves(t_compendium *all)
{
	int	op;
	int	exc;

	op = 12;
	exc = exclude(all);
	while (--op)
	{
		all->tns[op] = -1;
		if (exc & (1 << op))
		{
			all->done[all->n_st] |= 1 << op;
			continue ;
		}
		move(all, op);
		all->tns[op] = tot_tension(all);
		if (all->tns[op] > all->tns[0] + all->tolerance)
		{
			all->tns[op] = -1;
			all->done[all->n_st - 1] |= 1 << op;
		}
		undo(all, 1);
	}
}

void	save_part(t_compendium *all, int bt_z)
{
	int	i;

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

void	fan(t_compendium *all, int search_depth)
{
	int min_tns;
	int bt_z;
	int	pr_st;

	if (search_depth >= all->sol_st)
		search_depth = all->sol_st - 1;
	pr_st = 0;
	min_tns = all->tns[0];
	bt_z = all->n_st;
	while (all->n_st < search_depth && (bt_z < all->n_st || all->tns[0] > -1))
	{
		eval_moves(all);
		all->tns[0] = apply_min(all);
		if (all->tns[0] > -1 && all->tns[0] <= min_tns + 1)
		{
			if (all->tns[0] < min_tns)
				min_tns = all->tns[0];
			if (!all->tns[0])
				search_depth = all->n_st - 1;
			if (!all->tns[0] || all->tns[0] < all->part_tns)
				save_part(all, bt_z);
			if (all->part_tns > 0 && all->n_st > search_depth - 2)
				fan(all, all->n_st + BACKTRACK_DEPTH);
		}
		while (all->n_st > bt_z &&
			(all->n_st >= search_depth || all->tns[0] < 0))
			undo(all, 1);
	}
}