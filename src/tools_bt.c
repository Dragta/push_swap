#include "../push_swap.h"

int	min_step(t_compendium *all, int *op)
{
	int	min_tns;
	int	low;

/*	min_tns = all->tns[0] + all->tolerance;*/
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
/*	printf("tns %i->%i\n", all->tns[0], min_tns);*/
	return (min_tns);
}

void	init_next_st(t_compendium *all)
{
	all->steps[all->n_st + 1] = 0;
	all->done[all->n_st + 1] = 0;
	all->cut[all->n_st + 1] = all->cut[all->n_st];
	all->cut[all->n_st + 1] &= all->heir_mask[(int)all->steps[all->n_st]];
	all->cut[all->n_st + 1] |= all->cut_mask[(int)all->steps[all->n_st]];
	all->n_st++;
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

void	exclude_reps(t_compendium *all)
{
	int	op;
	int	id;
	int	i;

	op = all->steps[all->n_st - 1];
	id = -1;
	if (OPS_A & (1 << op))
		id = 0;
	if (OPS_B & (1 << op))
		id = 1;
	if (id != -1 && !all->count_blocked[id])
	{
		i = all->count[id] / 2;
		if (NOT_REP & (1 << op) && i <= all->n_st)
		{
			while (i && all->steps[all->n_st - i] == op)
				i--;
			if (!i)
				all->cut[all->n_st] |= 1 << op;
		}
	}
}

int	exclude(t_compendium *all)
{
	int	ret;

/*	if (all->n_st > 80)
	{
		printf("ct0 %i, ctBL0 %i\n", all->count[0], all->count_blocked[0]);
		printf("ct1 %i, ctBL1 %i\n", all->count[1], all->count_blocked[1]);
		if (all->top[0])
			printf("pre_top0 %p, ", all->top[0]->prev);
		else
			printf("pre_top0 (NA), ");
		printf("top0 %p, topBL0 %p\n", all->top[0], all->block_top[0]);
		if (all->top[1])
			printf("pre_top1 %p, ", all->top[1]->prev);
		else
			printf("pre_top1 (NA), ");
		printf("top1 %p, topBL1 %p\n", all->top[1], all->block_top[1]);
	}*/
/*	exclude_reps(all);*/
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
	if (all->top[0] && all->top[0]->next == all->block_top[0])/*(all->block[0] < 2)*/
		ret |= NOT_1TOP_A;
	if ((all->count[1] - all->count_blocked[1]) < 2)
		ret |= NOT_1B;
	if (all->top[1] && all->top[1]->next == all->block_top[1])/*(all->block[1] < 2)*/
		ret |= NOT_1TOP_B;
	if ((all->count[0] - all->count_blocked[0]) < 3)
		ret |= NOT_2A;
	if ((all->count[1] - all->count_blocked[1]) < 3)
		ret |= NOT_2B;
	if (all->top[0] && all->top[0]->prev == all->block_btm[0])/*(all->block[0] + 1 == all->count[0])*/
		ret |= NOT_0BTM_A;
	if (all->top[1] && all->top[1]->prev == all->block_btm[1])/*(all->block[1] + 1 == all->count[1])*/
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
		if ((*(all->ops[op]))(all) <= 0)
		{
			printf("No undo %i with %i possible. Stack A: %i; Stack B: %i\n", all->steps[all->n_st - 1], op, all->count[0], all->count[1]);
			break ;
		}
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

/*	quick_st(all);
	printf("w(%i/%i), done[%i]=%i", all->tns[0], all->part_tns, all->n_st, all->done[all->n_st]);*/
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
/*		if (all->count_blocked[0] == 8)
			printf("step: %i\n", all->steps[all->n_st - 1]);*/
		if (all->steps[all->n_st - 1] <= 0)
		{
			printf("XXXXXXXXXXXXXXXXXX%i", op);
			all->tns[op] = -1;
			all->n_st--;
			all->done[all->n_st] |= 1 << op;
			count_stacks(all);
		}
		else
		{
			all->tns[op] = tot_tension(all);
			if (all->tns[op] > all->tns[0] + all->tolerance)
			{
				all->tns[op] = -1;
				all->done[all->n_st - 1] |= 1 << op;
			}
			undo(all, 1);
		}
	}
}

/*
void	eval_moves(t_compendium *all)
{
	int	op;

*	quick_st(all);
	printf("w(%i/%i), done[%i]=%i", all->tns[0], all->sol_tns, all->n_st, all->done[all->n_st]);*
	op = 12;
	while (--op)
	{
		all->tns[op] = -1;
		if (exclude(all) & (1 << op))
		{
			all->done[all->n_st] |= 1 << op;
			continue ;
		}
		all->steps[all->n_st] = (*(all->ops[op]))(all);
		if (all->steps[all->n_st] <= 0)
		{
			all->done[all->n_st] |= 1 << op;
			continue ;
		}
		if (all->steps[all->n_st] == op)
			all->tns[op] = tot_tension(all);
		if (all->tns[op] > all->tns[0] + all->tolerance)
		{
			all->tns[op] = -1;
			all->done[all->n_st] |= 1 << op;
		}
		all->n_st++;
		undo(all, 1);
	}
}*/

void	save_part(t_compendium *all, int bt_z)
{
	int	i;

/*	printf("\nsave_part:\ntns[0]: %i tot_tns: %i\n---\n", all->tns[0], tot_tension(all));*/
	all->part_tns = all->tns[0];
/*	if (all->n_st > 80)
	{
		write(1, "\n", 1);
		show_tgts(all);
		printf("\n min=%i, mejor tns: %i (%i steps) ", all->min_target, all->part_tns, all->n_st);
		quick_st(all);
		write(1, "\n---\n", 5);
	}*/
	i = all->n_st;
	all->part[i] = 0;
	while (--i >= bt_z)
		all->part[i] = all->steps[i];
	if (!all->part_tns)
	{
/*		write(1, "0", 1);*/
		i = all->n_st + 1;
		while (--i >= 0)
			all->sol[i] = all->steps[i];
		all->sol_st = all->n_st;
	}
}
/*
void	up_tolerance(t_compendium *all)
{
	if (all->tolerance < 1000)
		all->tolerance += all->tolerance / 10;
	all->done[all->n_st] = 0;
	all->sol_tns += all->tolerance;
	printf("n_st %i; up tolerance: %i\n", all->n_st, all->tolerance);
}*/

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
